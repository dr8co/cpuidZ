#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#if defined(__GNUC__) || defined(__clang__)
#include <cpuid.h>
#elif defined(_MSC_VER)
#include <intrin.h>
#endif


// Features in ecx for CPUID leaf 1
enum ecx_leaf1_features {
    b_SSE3 = 0x00000001,
    b_PCLMULQDQ = 0x00000002,
    b_DTES64 = 0x00000004,
    b_MONITOR = 0x00000008,
    b_DSCPL = 0x00000010,
    b_VMX = 0x00000020,
    b_SMX = 0x00000040,
    b_EIST = 0x00000080,
    b_TM2 = 0x00000100,
    b_SSSE3 = 0x00000200,
    b_CNXTID = 0x00000400,
    b_FMA = 0x00001000,
    b_CMPXCHG16B = 0x00002000,
    b_xTPR = 0x00004000,
    b_PDCM = 0x00008000,
    b_PCID = 0x00020000,
    b_DCA = 0x00040000,
    b_SSE41 = 0x00080000,
    b_SSE42 = 0x00100000,
    b_x2APIC = 0x00200000,
    b_MOVBE = 0x00400000,
    b_POPCNT = 0x00800000,
    b_TSCDeadline = 0x01000000,
    b_AESNI = 0x02000000,
    b_XSAVE = 0x04000000,
    b_OSXSAVE = 0x08000000,
    b_AVX = 0x10000000,
    b_F16C = 0x20000000,
    b_RDRND = 0x40000000,
};

// Features in edx for leaf 1
enum edx_leaf1_features {
    b_FPU = 0x00000001,
    b_VME = 0x00000002,
    b_DE = 0x00000004,
    b_PSE = 0x00000008,
    b_TSC = 0x00000010,
    b_MSR = 0x00000020,
    b_PAE = 0x00000040,
    b_MCE = 0x00000080,
    b_CX8 = 0x00000100,
    b_APIC = 0x00000200,
    b_SEP = 0x00000800,
    b_MTRR = 0x00001000,
    b_PGE = 0x00002000,
    b_MCA = 0x00004000,
    b_CMOV = 0x00008000,
    b_PAT = 0x00010000,
    b_PSE36 = 0x00020000,
    b_PSN = 0x00040000,
    b_CLFSH = 0x00080000,
    b_DS = 0x00200000,
    b_ACPI = 0x00400000,
    b_MMX = 0x00800000,
    b_FXSR = 0x01000000,
    b_SSE = 0x02000000,
    b_SSE2 = 0x04000000,
    b_SS = 0x08000000,
    b_HTT = 0x10000000,
    b_TM = 0x20000000,
    b_PBE = 0x80000000,
};

// Features in ebx for leaf 7 sub-leaf 0
enum ebx_leaf7_0_features {
    b_FSGSBASE = 0x00000001,
    b_SGX = 0x00000004,
    b_BMI = 0x00000008,
    b_HLE = 0x00000010,
    b_AVX2 = 0x00000020,
    b_SMEP = 0x00000080,
    b_BMI2 = 0x00000100,
    b_ENH_MOVSB = 0x00000200,
    b_INVPCID = 0x00000400,
    b_RTM = 0x00000800,
    b_MPX = 0x00004000,
    b_AVX512F = 0x00010000,
    b_AVX512DQ = 0x00020000,
    b_RDSEED = 0x00040000,
    b_ADX = 0x00080000,
    b_AVX512IFMA = 0x00200000,
    b_CLFLUSHOPT = 0x00800000,
    b_CLWB = 0x01000000,
    b_AVX512PF = 0x04000000,
    b_AVX512ER = 0x08000000,
    b_AVX512CD = 0x10000000,
    b_SHA = 0x20000000,
    b_AVX512BW = 0x40000000,
    b_AVX512VL = 0x80000000,
};

// Features in ecx for leaf 7 sub-leaf 0
enum ecx_leaf7_0_features {
    b_PREFTCHWT1 = 0x00000001,
    b_AVX512VBMI = 0x00000002,
    b_PKU = 0x00000004,
    b_OSPKE = 0x00000010,
    b_WAITPKG = 0x00000020,
    b_AVX512VBMI2 = 0x00000040,
    b_SHSTK = 0x00000080,
    b_GFNI = 0x00000100,
    b_VAES = 0x00000200,
    b_VPCLMULQDQ = 0x00000400,
    b_AVX512VNNI = 0x00000800,
    b_AVX512BITALG = 0x00001000,
    b_AVX512VPOPCNTDQ = 0x00004000,
    b_RDPID = 0x00400000,
    b_CLDEMOTE = 0x02000000,
    b_MOVDIRI = 0x08000000,
    b_MOVDIR64B = 0x10000000,
    b_ENQCMD = 0x20000000,
};


// Features in edx for leaf 7 sub-leaf 0
enum edx_leaf7_0_features {
    b_AVX5124VNNIW = 0x00000004,
    b_AVX5124FMAPS = 0x00000008,
    b_UINTR = 0x00000020,
    b_AVX512VP2INTERSECT = 0x00000100,
    b_SERIALIZE = 0x00004000,
    b_TSXLDTRK = 0x00010000,
    b_PCONFIG = 0x00040000,
    b_IBT = 0x00100000,
    b_AMXBF16 = 0x00400000,
    b_AVX512FP16 = 0x00800000,
    b_AMXTILE = 0x01000000,
    b_AMXINT8 = 0x02000000,
};

// Features in eax for leaf 7 sub-leaf 1
enum eax_leaf7_1_features {
    b_SHA512 = 0x00000001,
    b_SM3 = 0x00000002,
    b_SM4 = 0x00000004,
    b_RAOINT = 0x00000008,
    b_AVXVNNI = 0x00000010,
    b_AVX512BF16 = 0x00000020,
    b_CMPCCXADD = 0x00000080,
    b_AMXFP16 = 0x00200000,
    b_HRESET = 0x00400000,
    b_AVXIFMA = 0x00800000,
    b_MOVRS = 0x80000000,
};

// Features in edx for leaf 7 sub-leaf 1
enum edx_leaf7_1_features {
    b_AVXVNNIINT8 = 0x00000010,
    b_AVXNECONVERT = 0x00000020,
    b_AMXCOMPLEX = 0x00000100,
    b_AVXVNNIINT16 = 0x00000400,
    b_PREFETCHI = 0x00004000,
    b_USERMSR = 0x00008000,
    b_AVX10 = 0x00080000,
    b_APXF = 0x00200000,
};

// Features in eax for leaf 13 sub-leaf 1
enum eax_leaf13_1_features {
    b_XSAVEOPT = 0x00000001,
    b_XSAVEC = 0x00000002,
    b_XSAVES = 0x00000008,
};

// Features in ebx for leaf 0x14 sub-leaf 0
enum ebx_0x14_0_features {
    b_PTWRITE = 0x00000010,
};

// Features in ecx for leaf 0x80000001
enum ecx_0x80000001_features {
    b_LAHF_LM = 0x00000001,
    b_ABM = 0x00000020,
    b_SSE4a = 0x00000040,
    b_PRFCHW = 0x00000100,
    b_XOP = 0x00000800,
    b_LWP = 0x00008000,
    b_FMA4 = 0x00010000,
    b_TBM = 0x00200000,
    b_MWAITX = 0x20000000,
};

// Features in edx for leaf 0x80000001
enum edx_0x80000001_features {
    b_MMXEXT = 0x00400000,
    b_LM = 0x20000000,
    b_3DNOWP = 0x40000000,
    b_3DNOW = 0x80000000,
};

// Features in ebx for leaf 0x80000008
enum ebx_0x80000008_features {
    b_CLZERO = 0x00000001,
    b_RDPRU = 0x00000010,
    b_WBNOINVD = 0x00000200,
};

// Features in ebx for leaf 0x24
enum ebx_0x24_features {
    b_AVX10_256 = 0x00020000,
    b_AVX10_512 = 0x00040000,
};

// AMX sub-leaf (%eax == 0x1e, %ecx == 1)
enum amx_features {
    b_AMXFP8 = 0x00000010,
    b_AMX_TRANSPOSE = 0x00000020,
    b_AMX_TF32 = 0x00000040,
    b_AMX_AVX512 = 0x00000080,
    b_AMX_MOVRS = 0x00000100,
};

// Keylocker leaf (%eax == 0x19)
enum keylocker_features {
    b_AESKLE = 0x00000001,
    b_WIDEKL = 0x00000004,
};

// CPU signatures
enum cpu_signatures {
    // AMD: "AuthenticAMD"
    AMD_ebx = 0x68747541,
    AMD_edx = 0x69746e65,
    AMD_ecx = 0x444d4163,

    // CENTAUR: "CentaurHauls"
    CENTAUR_ebx = 0x746e6543,
    CENTAUR_edx = 0x48727561,
    CENTAUR_ecx = 0x736c7561,

    // CYRIX: "CyrixInstead"
    CYRIX_ebx = 0x69727943,
    CYRIX_edx = 0x736e4978,
    CYRIX_ecx = 0x64616574,

    // HYGON: "HygonGenuine"
    HYGON_ebx = 0x6f677948,
    HYGON_edx = 0x6e65476e,
    HYGON_ecx = 0x656e6975,

    // INTEL: "GenuineIntel"
    INTEL_ebx = 0x756e6547,
    INTEL_edx = 0x49656e69,
    INTEL_ecx = 0x6c65746e,

    // TM1: "TransmetaCPU"
    TM1_ebx = 0x6e617254,
    TM1_edx = 0x74656d73,
    TM1_ecx = 0x55504361,

    // TM2: "GenuineTMx86"
    TM2_ebx = 0x756e6547,
    TM2_edx = 0x54656e69,
    TM2_ecx = 0x3638784d,

    // NSC: "Geode by NSC"
    NSC_ebx = 0x646f6547,
    NSC_edx = 0x79622065,
    NSC_ecx = 0x43534e20,

    // NEXGEN: "NexGenDriven"
    NEXGEN_ebx = 0x4778654e,
    NEXGEN_edx = 0x72446e65,
    NEXGEN_ecx = 0x6e657669,

    // RISE: "RiseRiseRise"
    RISE_ebx = 0x65736952,
    RISE_edx = 0x65736952,
    RISE_ecx = 0x65736952,

    // SIS: "SiS SiS SiS "
    SIS_ebx = 0x20536953,
    SIS_edx = 0x20536953,
    SIS_ecx = 0x20536953,

    // UMC: "UMC UMC UMC "
    UMC_ebx = 0x20434d55,
    UMC_edx = 0x20434d55,
    UMC_ecx = 0x20434d55,

    // VIA: "VIA VIA VIA "
    VIA_ebx = 0x20414956,
    VIA_edx = 0x20414956,
    VIA_ecx = 0x20414956,

    // VORTEX: "Vortex86 SoC"
    VORTEX_ebx = 0x74726f56,
    VORTEX_edx = 0x36387865,
    VORTEX_ecx = 0x436f5320,
};

struct cpu_basic_info {
    char vendor[13];
    char brand[49];
    uint32_t family;
    uint32_t model;
    uint32_t stepping;
};

struct cpu_features {
    bool SSE3;
    bool PCLMULQDQ;
    bool DTES64;
    bool MONITOR;
    bool DSCPL;
    bool VMX;
    bool SMX;
    bool EIST;
    bool TM2;
    bool SSSE3;
    bool CNXTID;
    bool FMA;
    bool CMPXCHG16B;
    bool xTPR;
    bool PDCM;
    bool PCID;
    bool DCA;
    bool SSE41;
    bool SSE42;
    bool x2APIC;
    bool MOVBE;
    bool POPCNT;
    bool TSCDeadline;
    bool AESNI;
    bool XSAVE;
    bool OSXSAVE;
    bool AVX;
    bool F16C;
    bool RDRND;
    bool FPU;
    bool VME;
    bool DE;
    bool PSE;
    bool TSC;
    bool MSR;
    bool PAE;
    bool MCE;
    bool CX8;
    bool APIC;
    bool SEP;
    bool MTRR;
    bool PGE;
    bool MCA;
    bool CMOV;
    bool PAT;
    bool PSE36;
    bool PSN;
    bool CLFSH;
    bool DS;
    bool ACPI;
    bool MMX;
    bool FXSR;
    bool SSE;
    bool SSE2;
    bool SS;
    bool HTT;
    bool TM;
    bool PBE;
    bool FSGSBASE;
    bool SGX;
    bool BMI;
    bool HLE;
    bool AVX2;
    bool SMEP;
    bool BMI2;
    bool ENH_MOVSB;
    bool INVPCID;
    bool RTM;
    bool MPX;
    bool AVX512F;
    bool AVX512DQ;
    bool RDSEED;
    bool ADX;
    bool AVX512IFMA;
    bool CLFLUSHOPT;
    bool CLWB;
    bool AVX512PF;
    bool AVX512ER;
    bool AVX512CD;
    bool SHA;
    bool AVX512BW;
    bool AVX512VL;
    bool PREFTCHWT1;
    bool AVX512VBMI;
    bool PKU;
    bool OSPKE;
    bool WAITPKG;
    bool AVX512VBMI2;
    bool SHSTK;
    bool GFNI;
    bool VAES;
    bool VPCLMULQDQ;
    bool AVX512VNNI;
    bool AVX512BITALG;
    bool AVX512VPOPCNTDQ;
    bool RDPID;
    bool CLDEMOTE;
    bool MOVDIRI;
    bool MOVDIR64B;
    bool ENQCMD;
    bool AVX5124VNNIW;
    bool AVX5124FMAPS;
    bool UINTR;
    bool AVX512VP2INTERSECT;
    bool SERIALIZE;
    bool TSXLDTRK;
    bool PCONFIG;
    bool IBT;
    bool AMXBF16;
    bool AVX512FP16;
    bool AMXTILE;
    bool AMXINT8;
    bool SHA512;
    bool SM3;
    bool SM4;
    bool RAOINT;
    bool AVXVNNI;
    bool AVX512BF16;
    bool CMPCCXADD;
    bool AMXFP16;
    bool HRESET;
    bool AVXIFMA;
    bool MOVRS;
    bool AVXVNNIINT8;
    bool AVXNECONVERT;
    bool AMXCOMPLEX;
    bool AVXVNNIINT16;
    bool PREFETCHI;
    bool USERMSR;
    bool AVX10;
    bool APXF;
    bool XSAVEOPT;
    bool XSAVEC;
    bool XSAVES;
    bool PTWRITE;
    bool LAHF_LM;
    bool ABM;
    bool SSE4a;
    bool PRFCHW;
    bool XOP;
    bool LWP;
    bool FMA4;
    bool TBM;
    bool MWAITX;
    bool MMXEXT;
    bool LM;
    bool a3DNOWP;
    bool a3DNOW;
    bool CLZERO;
    bool RDPRU;
    bool WBNOINVD;
    bool AVX10_256;
    bool AVX10_512;
    bool AMXFP8;
    bool AMX_TRANSPOSE;
    bool AMX_TF32;
    bool AMX_AVX512;
    bool AMX_MOVRS;
    bool AESKLE;
    bool WIDEKL;
};

// Function to execute the CPUID instruction
void cpuid(uint32_t leaf, uint32_t registers[4]) {
#if defined(__GNUC__) || defined(__clang__)
    __cpuid(leaf, registers[0], registers[1], registers[2], registers[3]);
#elif defined(_MSC_VER)
    __cpuid(registers, leaf);
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

// Function to check specific feature availability in a register
int is_feature_supported(const uint32_t reg, const int bit) {
    return (reg & (1 << bit)) != 0;
}

extern int check_cpuid();

int main() {
    const int supported = check_cpuid();
    if (supported) {
        printf("CPUID is supported.\n");
    } else {
        printf("CPUID is not supported.\n");
        return 1;
    }


    uint32_t registers[4] = {0}; // Registers: EAX, EBX, ECX, EDX

    // Query the basic CPUID information
    cpuid(0, registers);
    const uint32_t highest_leaf = registers[0];
    printf("Highest CPUID leaf: %u\n", highest_leaf);

    // Check for standard feature flags (CPUID Leaf 1)
    cpuid(1, registers);
    printf("Checking Standard Feature Flags (CPUID Leaf 1):\n");

    // EDX flags
    printf(" - SSE: %s\n", is_feature_supported(registers[3], 25) ? "Supported" : "Not supported");
    printf(" - SSE2: %s\n", is_feature_supported(registers[3], 26) ? "Supported" : "Not supported");

    // ECX flags
    printf(" - SSE3: %s\n", is_feature_supported(registers[2], 0) ? "Supported" : "Not supported");
    printf(" - SSSE3: %s\n", is_feature_supported(registers[2], 9) ? "Supported" : "Not supported");
    printf(" - SSE4.1: %s\n", is_feature_supported(registers[2], 19) ? "Supported" : "Not supported");
    printf(" - SSE4.2: %s\n", is_feature_supported(registers[2], 20) ? "Supported" : "Not supported");
    printf(" - AVX: %s\n", is_feature_supported(registers[2], 28) ? "Supported" : "Not supported");
    printf(" - AES: %s\n", is_feature_supported(registers[2], 25) ? "Supported" : "Not supported");
    printf(" - FMA: %s\n", is_feature_supported(registers[2], 12) ? "Supported" : "Not supported");

    // Check for extended feature flags (CPUID Leaf 7)
    if (highest_leaf >= 7) {
        cpuid(7, registers);
        printf("Checking Extended Feature Flags (CPUID Leaf 7):\n");

        // EBX flags
        printf(" - AVX2: %s\n", is_feature_supported(registers[1], 5) ? "Supported" : "Not supported");
        printf(" - AVX512F: %s\n", is_feature_supported(registers[1], 16) ? "Supported" : "Not supported");
        printf(" - AVX512DQ: %s\n", is_feature_supported(registers[1], 17) ? "Supported" : "Not supported");
        printf(" - AVX512BW: %s\n", is_feature_supported(registers[1], 30) ? "Supported" : "Not supported");
        printf(" - AVX512VL: %s\n", is_feature_supported(registers[1], 31) ? "Supported" : "Not supported");
        printf(" - BMI1: %s\n", is_feature_supported(registers[1], 3) ? "Supported" : "Not supported");
        printf(" - BMI2: %s\n", is_feature_supported(registers[1], 8) ? "Supported" : "Not supported");
        printf(" - SHA: %s\n", is_feature_supported(registers[1], 29) ? "Supported" : "Not supported");
    } else {
        printf("Extended feature flags not supported on this CPU.\n");
    }

    return 0;
}
