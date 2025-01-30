#include "cpuidx.h"
#include <string.h>

#if defined(__GNUC__) || defined(__clang__)
#include <cpuid.h>
#elif defined(_MSC_VER)
#include <intrin.h>
#endif

/**
 * Function to execute the CPUID instruction.
 *
 * @param leaf The CPUID leaf to query.
 * @param registers An array to store the values of the registers EAX, EBX, ECX, and EDX.
 */
void cpuid(uint32_t leaf, uint32_t registers[4]) {
#if defined(__GNUC__) || defined(__clang__)
    __cpuid(leaf, registers[0], registers[1], registers[2], registers[3]);
#elif defined(_MSC_VER)
    __cpuid((int *) registers, (int) leaf);
#else
#ifdef __x86_64__
    __asm__ volatile (
        "  xchgq  %%rbx,%q1\n"
        "  cpuid\n"
        "  xchgq  %%rbx,%q1"
        : "=a" (registers[0]), "=r" (registers[1]), "=c" (registers[2]), "=d" (registers[3])
        : "0" (leaf));
#else
    __asm__ volatile (
        "cpuid\n"
        : "=a" (registers[0]), "=b" (registers[1]), "=c" (registers[2]), "=d" (registers[3])
        : "0" (leaf));
#endif
#endif
}

/**
 * Function to query extended features using the CPUID instruction.
 *
 * @param leaf The CPUID leaf to query.
 * @param sub_leaf The CPUID sub-leaf to query.
 * @param registers An array to store the values of the registers EAX, EBX, ECX, and EDX.
 */
void cpuid_extended(uint32_t leaf, uint32_t sub_leaf, uint32_t registers[4]) {
#if defined(__GNUC__) || defined(__clang__)
    __cpuid_count(leaf, sub_leaf, registers[0], registers[1], registers[2], registers[3]);
#elif defined(_MSC_VER)
    __cpuidex((int *) registers, (int) leaf, (int) sub_leaf);
#else
#ifdef __x86_64__
    __asm__ volatile (
        "  xchgq  %%rbx,%q1\n"
        "  cpuid\n"
        "  xchgq  %%rbx,%q1"
        : "=a" (registers[0]), "=r" (registers[1]), "=c" (registers[2]), "=d" (registers[3])
        : "0" (leaf), "2" (sub_leaf));
#else
    __asm__ volatile (
        "cpuid\n"
        : "=a" (registers[0]), "=b" (registers[1]), "=c" (registers[2]), "=d" (registers[3])
        : "0" (leaf), "2" (sub_leaf));
#endif
#endif
}

/**
 * Function to get CPU features and basic information.
 *
 * @param features A pointer to a \p cpu_features structure to store the CPU features.
 * @param basic_info A pointer to a \p cpu_basic_info structure to store the basic CPU information.
 * @return 0 on success, -1 if CPUID instruction is not supported, 1 if highest leaf is 0.
 */
int get_cpu_features(cpu_features* features, cpu_basic_info* basic_info) {
    if (!check_cpuid()) return -1;

    uint32_t registers[4] = {0}; // Registers: EAX, EBX, ECX, EDX

    // Query the basic CPUID information
    cpuid(0, registers);

    if ((basic_info->highest_leaf = registers[0])) {
        // The vendor string must be null-terminated
        memset(basic_info->vendor, '\0', 13);

        // Copy the vendor string
        memcpy(basic_info->vendor, &registers[1], 4);
        memcpy(basic_info->vendor + 4, &registers[3], 4);
        memcpy(basic_info->vendor + 8, &registers[2], 4);

        // Highest extended function calling parameter
        cpuid(0x80000000, registers);
        basic_info->highest_extended_leaf = registers[0];

        // Check for the CPU brand string
        if (basic_info->highest_extended_leaf >= 0x80000004) {
            // Ensure the brand string is null-terminated
            memset(basic_info->brand, '\0', 49);

            // Get the brand string
            cpuid(0x80000002, registers);
            memcpy(basic_info->brand, registers, 16);
            cpuid(0x80000003, registers);
            memcpy(basic_info->brand + 16, registers, 16);
            cpuid(0x80000004, registers);
            memcpy(basic_info->brand + 32, registers, 16);
        }

        // Check for the CPU family, model, and stepping
        cpuid(1, registers);
        basic_info->family = ((registers[0] >> 8) & 0xF) + ((registers[0] >> 20) & 0xFF);
        basic_info->model = ((registers[0] >> 4) & 0xF) + ((registers[0] >> 12) & 0xF0);
        basic_info->stepping = registers[0] & 0xF;

        // Standard feature flags (CPUID Leaf 1)
        // %ecx flags
        features->SSE3 = registers[2] & b_SSE3;
        features->PCLMULQDQ = registers[2] & b_PCLMULQDQ;
        features->DTES64 = registers[2] & b_DTES64;
        features->MONITOR = registers[2] & b_MONITOR;
        features->DSCPL = registers[2] & b_DSCPL;
        features->VMX = registers[2] & b_VMX;
        features->SMX = registers[2] & b_SMX;
        features->EIST = registers[2] & b_EIST;
        features->TM2 = registers[2] & b_TM2;
        features->SSSE3 = registers[2] & b_SSSE3;
        features->CNXTID = registers[2] & b_CNXTID;
        features->SDBG = registers[2] & b_SDBG;
        features->FMA = registers[2] & b_FMA;
        features->CMPXCHG16B = registers[2] & b_CMPXCHG16B;
        features->xTPR = registers[2] & b_xTPR;
        features->PDCM = registers[2] & b_PDCM;
        features->PCID = registers[2] & b_PCID;
        features->DCA = registers[2] & b_DCA;
        features->SSE41 = registers[2] & b_SSE41;
        features->SSE42 = registers[2] & b_SSE42;
        features->x2APIC = registers[2] & b_x2APIC;
        features->MOVBE = registers[2] & b_MOVBE;
        features->POPCNT = registers[2] & b_POPCNT;
        features->TSCDeadline = registers[2] & b_TSCDeadline;
        features->AESNI = registers[2] & b_AESNI;
        features->XSAVE = registers[2] & b_XSAVE;
        features->OSXSAVE = registers[2] & b_OSXSAVE;
        features->AVX = registers[2] & b_AVX;
        features->F16C = registers[2] & b_F16C;
        features->RDRND = registers[2] & b_RDRND;
        features->HYPRVSR = registers[2] & b_HYPRVSR;

        // %edx flags
        features->FPU = registers[3] & b_FPU;
        features->VME = registers[3] & b_VME;
        features->DE = registers[3] & b_DE;
        features->PSE = registers[3] & b_PSE;
        features->TSC = registers[3] & b_TSC;
        features->MSR = registers[3] & b_MSR;
        features->PAE = registers[3] & b_PAE;
        features->MCE = registers[3] & b_MCE;
        features->CX8 = registers[3] & b_CX8;
        features->APIC = registers[3] & b_APIC;
        features->SEP = registers[3] & b_SEP;
        features->MTRR = registers[3] & b_MTRR;
        features->PGE = registers[3] & b_PGE;
        features->MCA = registers[3] & b_MCA;
        features->CMOV = registers[3] & b_CMOV;
        features->PAT = registers[3] & b_PAT;
        features->PSE36 = registers[3] & b_PSE36;
        features->PSN = registers[3] & b_PSN;
        features->CLFSH = registers[3] & b_CLFSH;
        features->DS = registers[3] & b_DS;
        features->ACPI = registers[3] & b_ACPI;
        features->MMX = registers[3] & b_MMX;
        features->FXSR = registers[3] & b_FXSR;
        features->SSE = registers[3] & b_SSE;
        features->SSE2 = registers[3] & b_SSE2;
        features->SS = registers[3] & b_SS;
        features->HTT = registers[3] & b_HTT;
        features->TM = registers[3] & b_TM;
        features->IA64 = registers[3] & b_IA64;
        features->PBE = registers[3] & b_PBE;

        // Check for extended feature flags (CPUID Leaf 7)
        if (basic_info->highest_leaf >= 7) {
            // sub-leaf 0
            cpuid_extended(7, 0, registers);

            // %ebx flags
            features->FSGSBASE = registers[1] & b_FSGSBASE;
            features->SGX = registers[1] & b_SGX;
            features->BMI = registers[1] & b_BMI;
            features->HLE = registers[1] & b_HLE;
            features->FDPXO = registers[1] & b_FDPXO;
            features->AVX2 = registers[1] & b_AVX2;
            features->SMEP = registers[1] & b_SMEP;
            features->BMI2 = registers[1] & b_BMI2;
            features->ENH_MOVSB = registers[1] & b_ENH_MOVSB;
            features->INVPCID = registers[1] & b_INVPCID;
            features->RTM = registers[1] & b_RTM;
            features->MPX = registers[1] & b_MPX;
            features->AVX512F = registers[1] & b_AVX512F;
            features->AVX512DQ = registers[1] & b_AVX512DQ;
            features->RDSEED = registers[1] & b_RDSEED;
            features->ADX = registers[1] & b_ADX;
            features->SMAP = registers[1] & b_SMAP;
            features->AVX512IFMA = registers[1] & b_AVX512IFMA;
            features->CLFLUSHOPT = registers[1] & b_CLFLUSHOPT;
            features->CLWB = registers[1] & b_CLWB;
            features->PT = registers[1] & b_PT;
            features->AVX512PF = registers[1] & b_AVX512PF;
            features->AVX512ER = registers[1] & b_AVX512ER;
            features->AVX512CD = registers[1] & b_AVX512CD;
            features->SHA = registers[1] & b_SHA;
            features->AVX512BW = registers[1] & b_AVX512BW;
            features->AVX512VL = registers[1] & b_AVX512VL;

            // %ecx flags
            features->PREFTCHWT1 = registers[2] & b_PREFTCHWT1;
            features->AVX512VBMI = registers[2] & b_AVX512VBMI;
            features->UMIP = registers[2] & b_UMIP;
            features->PKU = registers[2] & b_PKU;
            features->OSPKE = registers[2] & b_OSPKE;
            features->WAITPKG = registers[2] & b_WAITPKG;
            features->AVX512VBMI2 = registers[2] & b_AVX512VBMI2;
            features->SHSTK = registers[2] & b_SHSTK;
            features->GFNI = registers[2] & b_GFNI;
            features->VAES = registers[2] & b_VAES;
            features->VPCLMULQDQ = registers[2] & b_VPCLMULQDQ;
            features->AVX512VNNI = registers[2] & b_AVX512VNNI;
            features->AVX512BITALG = registers[2] & b_AVX512BITALG;
            features->TMEM = registers[2] & b_TMEM;
            features->AVX512VPOPCNTDQ = registers[2] & b_AVX512VPOPCNTDQ;
            features->IA57 = registers[2] & b_IA57;
            features->RDPID = registers[2] & b_RDPID;
            features->KL = registers[2] & b_KL;
            features->BLD = registers[2] & b_BLD;
            features->CLDEMOTE = registers[2] & b_CLDEMOTE;
            features->MOVDIRI = registers[2] & b_MOVDIRI;
            features->MOVDIR64B = registers[2] & b_MOVDIR64B;
            features->ENQCMD = registers[2] & b_ENQCMD;
            features->SGXLC = registers[2] & b_SGXLC;
            features->PKS = registers[2] & b_PKS;

            // %edx flags
            features->SGXKEYS = registers[3] & b_SGXKEYS;
            features->AVX5124VNNIW = registers[3] & b_AVX5124VNNIW;
            features->AVX5124FMAPS = registers[3] & b_AVX5124FMAPS;
            features->FSRM = registers[3] & b_FSRM;
            features->UINTR = registers[3] & b_UINTR;
            features->AVX512VP2INTERSECT = registers[3] & b_AVX512VP2INTERSECT;
            features->SRBDSCTRL = registers[3] & b_SRBDSCTRL;
            features->MDCLEAR = registers[3] & b_MDCLEAR;
            features->RTMAA = registers[3] & b_RTMAA;
            features->RTMFA = registers[3] & b_RTMFA;
            features->SERIALIZE = registers[3] & b_SERIALIZE;
            features->HYBRID = registers[3] & b_HYBRID;
            features->TSXLDTRK = registers[3] & b_TSXLDTRK;
            features->PCONFIG = registers[3] & b_PCONFIG;
            features->LBR = registers[3] & b_LBR;
            features->IBT = registers[3] & b_IBT;
            features->AMXBF16 = registers[3] & b_AMXBF16;
            features->AVX512FP16 = registers[3] & b_AVX512FP16;
            features->AMXTILE = registers[3] & b_AMXTILE;
            features->AMXINT8 = registers[3] & b_AMXINT8;
            features->IBRRS = registers[3] & b_IBRRS;
            features->STIBP = registers[3] & b_STIBP;
            features->L1D_FLUSH = registers[3] & b_L1D_FLUSH;
            features->IA32_ARCH_CAPABILITIES = registers[3] & b_IA32_ARCH_CAPABILITIES;
            features->IA32_CORE_CAPABILITIES = registers[3] & b_IA32_CORE_CAPABILITIES;
            features->SSBD = registers[3] & b_SSBD;

            // sub-leaf 1
            cpuid_extended(7, 1, registers);

            // %eax flags
            features->SHA512 = registers[0] & b_SHA512;
            features->SM3 = registers[0] & b_SM3;
            features->SM4 = registers[0] & b_SM4;
            features->RAOINT = registers[0] & b_RAOINT;
            features->AVXVNNI = registers[0] & b_AVXVNNI;
            features->AVX512BF16 = registers[0] & b_AVX512BF16;
            features->CMPCCXADD = registers[0] & b_CMPCCXADD;
            features->FRED = registers[0] & b_FRED;
            features->LKGS = registers[0] & b_LKGS;
            features->WRMSRNS = registers[0] & b_WRMSRNS;
            features->NMISRC = registers[0] & b_NMISRC;
            features->AMXFP16 = registers[0] & b_AMXFP16;
            features->HRESET = registers[0] & b_HRESET;
            features->AVXIFMA = registers[0] & b_AVXIFMA;
            features->MSRLIST = registers[0] & b_MSRLIST;
            features->MOVRS = registers[0] & b_MOVRS;

            // %ebx flags
            features->PBNDKB = registers[1] & b_PBNDKB;

            // %edx flags
            features->AVXVNNIINT8 = registers[3] & b_AVXVNNIINT8;
            features->AVXNECONVERT = registers[3] & b_AVXNECONVERT;
            features->AMXCOMPLEX = registers[3] & b_AMXCOMPLEX;
            features->AVXVNNIINT16 = registers[3] & b_AVXVNNIINT16;
            features->PREFETCHI = registers[3] & b_PREFETCHI;
            features->USERMSR = registers[3] & b_USERMSR;
            features->AVX10 = registers[3] & b_AVX10;
            features->APXF = registers[3] & b_APXF;
        }

        // Leaf 13
        if (basic_info->highest_leaf >= 13) {
            // sub-leaf 1
            cpuid_extended(13, 1, registers);

            // %eax flags
            features->XSAVEOPT = registers[0] & b_XSAVEOPT;
            features->XSAVEC = registers[0] & b_XSAVEC;
            features->XSAVES = registers[0] & b_XSAVES;
            features->XSAVEXFD = registers[0] & b_XSAVEXFD;
        }

        // Leaf 0x14
        if (basic_info->highest_leaf >= 0x14) {
            // sub-leaf 0
            cpuid_extended(0x14, 0, registers);

            // %ebx flags
            features->PTWRITE = registers[1] & b_PTWRITE;
        }

        // Keylocker leaf (leaf 0x19)
        if (basic_info->highest_extended_leaf >= 0x19) {
            cpuid(0x19, registers);

            // %eax flags
            features->AESKLE = registers[0] & b_AESKLE;
            features->WIDEKL = registers[0] & b_WIDEKL;
        }

        // AMX sub-leaf
        if (basic_info->highest_extended_leaf >= 0x1e) {
            // sub-leaf 1
            cpuid_extended(0x1e, 1, registers);

            // %eax flags
            features->AMXFP8 = registers[0] & b_AMXFP8;
            features->AMX_TRANSPOSE = registers[0] & b_AMX_TRANSPOSE;
            features->AMX_TF32 = registers[0] & b_AMX_TF32;
            features->AMX_AVX512 = registers[0] & b_AMX_AVX512;
            features->AMX_MOVRS = registers[0] & b_AMX_MOVRS;
        }

        // Leaf 0x24
        if (basic_info->highest_extended_leaf >= 0x24) {
            cpuid_extended(0x24, 0, registers);

            // %ebx flags
            features->AVX10_256 = registers[1] & b_AVX10_256;
            features->AVX10_512 = registers[1] & b_AVX10_512;
        }

        // Leaf 0x80000001
        if (basic_info->highest_extended_leaf >= 0x80000001) {
            cpuid(0x80000001, registers);

            // %ecx flags
            features->LAHF_LM = registers[2] & b_LAHF_LM;
            features->ABM = registers[2] & b_ABM;
            features->SSE4a = registers[2] & b_SSE4a;
            features->PRFCHW = registers[2] & b_PRFCHW;
            features->XOP = registers[2] & b_XOP;
            features->LWP = registers[2] & b_LWP;
            features->FMA4 = registers[2] & b_FMA4;
            features->TBM = registers[2] & b_TBM;
            features->MWAITX = registers[2] & b_MWAITX;

            // %edx flags
            features->MMXEXT = registers[3] & b_MMXEXT;
            features->LM = registers[3] & b_LM;
            features->x3DNOWP = registers[3] & b_3DNOWP;
            features->x3DNOW = registers[3] & b_3DNOW;
        }

        // Leaf 0x80000008
        if (basic_info->highest_extended_leaf >= 0x80000008) {
            cpuid(0x80000008, registers);

            // %ebx flags
            features->CLZERO = registers[1] & b_CLZERO;
            features->RDPRU = registers[1] & b_RDPRU;
            features->WBNOINVD = registers[1] & b_WBNOINVD;
        }

        return 0;
    }

    return 1;
}
