#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#if defined(__GNUC__) || defined(__clang__)
#include <cpuid.h>
#elif defined(_MSC_VER)
#include <intrin.h>
#endif


enum {
    // Features in ecx for CPUID leaf 1
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
    b_SDBG = 0x00000800,
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
    b_HYPRVSR = 0x80000000,

    // Features in edx for leaf 1
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
    b_IA64 = 0x40000000,
    b_PBE = 0x80000000,

    // Features in ebx for leaf 7 sub-leaf 0
    b_FSGSBASE = 0x00000001,
    b_SGX = 0x00000004,
    b_BMI = 0x00000008,
    b_HLE = 0x00000010,
    b_AVX2 = 0x00000020,
    b_FDPXO = 0x00000040,
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
    b_SMAP = 0x00100000,
    b_AVX512IFMA = 0x00200000,
    b_CLFLUSHOPT = 0x00800000,
    b_CLWB = 0x01000000,
    b_PT = 0x02000000,
    b_AVX512PF = 0x04000000,
    b_AVX512ER = 0x08000000,
    b_AVX512CD = 0x10000000,
    b_SHA = 0x20000000,
    b_AVX512BW = 0x40000000,
    b_AVX512VL = 0x80000000,

    // Features in ecx for leaf 7 sub-leaf 0
    b_PREFTCHWT1 = 0x00000001,
    b_AVX512VBMI = 0x00000002,
    b_UMIP = 0x00000004,
    b_PKU = 0x00000008,
    b_OSPKE = 0x00000010,
    b_WAITPKG = 0x00000020,
    b_AVX512VBMI2 = 0x00000040,
    b_SHSTK = 0x00000080,
    b_GFNI = 0x00000100,
    b_VAES = 0x00000200,
    b_VPCLMULQDQ = 0x00000400,
    b_AVX512VNNI = 0x00000800,
    b_AVX512BITALG = 0x00001000,
    b_TMEM = 0x00002000,
    b_AVX512VPOPCNTDQ = 0x00004000,
    b_IA57 = 0x00010000,
    b_RDPID = 0x00400000,
    b_KL = 0x00800000,
    b_BLD = 0x01000000,
    b_CLDEMOTE = 0x02000000,
    b_MOVDIRI = 0x08000000,
    b_MOVDIR64B = 0x10000000,
    b_ENQCMD = 0x20000000,
    b_SGXLC = 0x40000000,
    b_PKS = 0x80000000,

    // Features in edx for leaf 7 sub-leaf 0
    b_SGXKEYS = 0x00000002,
    b_AVX5124VNNIW = 0x00000004,
    b_AVX5124FMAPS = 0x00000008,
    b_FSRM = 0x00000010,
    b_UINTR = 0x00000020,
    b_AVX512VP2INTERSECT = 0x00000100,
    b_SRBDSCTRL = 0x00000200,
    b_MDCLEAR = 0x00000400,
    b_RTMAA = 0x00000800,
    b_RTMFA = 0x00002000,
    b_SERIALIZE = 0x00004000,
    b_HYBRID = 0x00008000,
    b_TSXLDTRK = 0x00010000,
    b_PCONFIG = 0x00040000,
    b_LBR = 0x00080000,
    b_IBT = 0x00100000,
    b_AMXBF16 = 0x00400000,
    b_AVX512FP16 = 0x00800000,
    b_AMXTILE = 0x01000000,
    b_AMXINT8 = 0x02000000,
    b_IBRRS = 0x04000000,
    b_STIBP = 0x08000000,
    b_L1D_FLUSH = 0x10000000,
    b_IA32_ARCH_CAPABILITIES = 0x20000000,
    b_IA32_CORE_CAPABILITIES = 0x40000000,
    b_SSBD = 0x80000000,

    // Features in eax for leaf 7 sub-leaf 1
    b_SHA512 = 0x00000001,
    b_SM3 = 0x00000002,
    b_SM4 = 0x00000004,
    b_RAOINT = 0x00000008,
    b_AVXVNNI = 0x00000010,
    b_AVX512BF16 = 0x00000020,
    b_CMPCCXADD = 0x00000080,
    b_FRED = 0x00020000,
    b_LKGS = 0x00040000,
    b_WRMSRNS = 0x00080000,
    b_NMISRC = 0x00100000,
    b_AMXFP16 = 0x00200000,
    b_HRESET = 0x00400000,
    b_AVXIFMA = 0x00800000,
    b_MSRLIST = 0x08000000,
    b_MOVRS = 0x80000000,

    // Features in ebx for leaf 7 sub-leaf 1
    b_PBNDKB = 0x00000002,

    // Features in edx for leaf 7 sub-leaf 1
    b_AVXVNNIINT8 = 0x00000010,
    b_AVXNECONVERT = 0x00000020,
    b_AMXCOMPLEX = 0x00000100,
    b_AVXVNNIINT16 = 0x00000400,
    b_PREFETCHI = 0x00004000,
    b_USERMSR = 0x00008000,
    b_AVX10 = 0x00080000,
    b_APXF = 0x00200000,

    // Features in eax for leaf 13 sub-leaf 1
    b_XSAVEOPT = 0x00000001,
    b_XSAVEC = 0x00000002,
    b_XSAVES = 0x00000008,
    b_XSAVEXFD = 0x00000010,

    // Features in ebx for leaf 0x14 sub-leaf 0
    b_PTWRITE = 0x00000010,

    // Keylocker leaf (%eax == 0x19)
    b_AESKLE = 0x00000001,
    b_WIDEKL = 0x00000004,

    // Features in %eax for AMX sub-leaf (%eax == 0x1e, %ecx == 1)
    b_AMXFP8 = 0x00000010,
    b_AMX_TRANSPOSE = 0x00000020,
    b_AMX_TF32 = 0x00000040,
    b_AMX_AVX512 = 0x00000080,
    b_AMX_MOVRS = 0x00000100,

    // Features in ebx for leaf 0x24
    b_AVX10_256 = 0x00020000,
    b_AVX10_512 = 0x00040000,

    // Features in ecx for leaf 0x80000001
    b_LAHF_LM = 0x00000001,
    b_ABM = 0x00000020,
    b_SSE4a = 0x00000040,
    b_PRFCHW = 0x00000100,
    b_XOP = 0x00000800,
    b_LWP = 0x00008000,
    b_FMA4 = 0x00010000,
    b_TBM = 0x00200000,
    b_MWAITX = 0x20000000,

    // Features in edx for leaf 0x80000001
    b_MMXEXT = 0x00400000,
    b_LM = 0x20000000,
    b_3DNOWP = 0x40000000,
    b_3DNOW = 0x80000000,

    // Features in ebx for leaf 0x80000008
    b_CLZERO = 0x00000001,
    b_RDPRU = 0x00000010,
    b_WBNOINVD = 0x00000200,
};

typedef struct {
    char vendor[13];
    char brand[49];
    uint32_t family;
    uint32_t model;
    uint32_t stepping;
    uint32_t highest_leaf;
    uint32_t highest_extended_leaf;
} cpu_basic_info;

typedef struct {
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
    bool SDBG;
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
    bool HYPRVSR;
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
    bool IA64;
    bool PBE;
    bool FSGSBASE;
    bool SGX;
    bool BMI;
    bool HLE;
    bool AVX2;
    bool FDPXO;
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
    bool SMAP;
    bool AVX512IFMA;
    bool CLFLUSHOPT;
    bool CLWB;
    bool PT;
    bool AVX512PF;
    bool AVX512ER;
    bool AVX512CD;
    bool SHA;
    bool AVX512BW;
    bool AVX512VL;
    bool PREFTCHWT1;
    bool AVX512VBMI;
    bool UMIP;
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
    bool TMEM;
    bool AVX512VPOPCNTDQ;
    bool IA57;
    bool RDPID;
    bool KL;
    bool BLD;
    bool CLDEMOTE;
    bool MOVDIRI;
    bool MOVDIR64B;
    bool ENQCMD;
    bool SGXLC;
    bool PKS;
    bool SGXKEYS;
    bool AVX5124VNNIW;
    bool AVX5124FMAPS;
    bool FSRM;
    bool UINTR;
    bool AVX512VP2INTERSECT;
    bool SRBDSCTRL;
    bool MDCLEAR;
    bool RTMAA;
    bool RTMFA;
    bool SERIALIZE;
    bool HYBRID;
    bool TSXLDTRK;
    bool PCONFIG;
    bool LBR;
    bool IBT;
    bool AMXBF16;
    bool AVX512FP16;
    bool AMXTILE;
    bool AMXINT8;
    bool IBRRS;
    bool STIBP;
    bool L1D_FLUSH;
    bool IA32_ARCH_CAPABILITIES;
    bool IA32_CORE_CAPABILITIES;
    bool SSBD;
    bool SHA512;
    bool SM3;
    bool SM4;
    bool RAOINT;
    bool AVXVNNI;
    bool AVX512BF16;
    bool CMPCCXADD;
    bool FRED;
    bool LKGS;
    bool WRMSRNS;
    bool NMISRC;
    bool AMXFP16;
    bool HRESET;
    bool AVXIFMA;
    bool MSRLIST;
    bool MOVRS;
    bool PBNDKB;
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
    bool XSAVEXFD;
    bool PTWRITE;
    bool AESKLE;
    bool WIDEKL;
    bool AMXFP8;
    bool AMX_TRANSPOSE;
    bool AMX_TF32;
    bool AMX_AVX512;
    bool AMX_MOVRS;
    bool AVX10_256;
    bool AVX10_512;
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
    bool x3DNOWP;
    bool x3DNOW;
    bool CLZERO;
    bool RDPRU;
    bool WBNOINVD;
} cpu_features;

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

// Function to query extended features
void cpuid_extended(uint32_t leaf, uint32_t sub_leaf, uint32_t registers[4]) {
#if defined(__GNUC__) || defined(__clang__)
    __cpuid_count(leaf, sub_leaf, registers[0], registers[1], registers[2], registers[3]);
#elif defined(_MSC_VER)
    __cpuidex(registers, leaf, subleaf);
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

// // Function to check specific feature availability in a register
// int is_feature_supported(const uint32_t reg, const int bit) {
//     return (reg & (1 << bit)) != 0;
// }

extern int check_cpuid();

void print_basic_info(const cpu_basic_info* const feat) {
    puts("Basic CPU Information:");
    if (feat->vendor[0] != '\0') printf("\tVendor: %s\n", feat->vendor);
    if (feat->brand[0] != '\0') printf("\tBrand: %s\n", feat->brand);
    if (feat->family) printf("\tFamily: %d\n", feat->family);
    if (feat->model) printf("\tModel: %d\n", feat->model);
    if (feat->stepping) printf("\tStepping id: %d\n", feat->stepping);
    if (feat->highest_leaf) printf("\tHighest leaf: 0x%x\n", feat->highest_leaf);
    if (feat->highest_extended_leaf) printf("\tHighest extended leaf: 0x%x\n", feat->highest_extended_leaf);
}

void print_available_features(const cpu_features* feats) {
    const char* feature_names[] = {
        "SSE3 (Prescott New Instructions - PNI)", "PCLMULQDQ  (carry-less multiply) instruction",
        "DTES64: 64-bit debug store", "MONITOR: MONITOR and MWAIT instructions (PNI)",
        "DSCPL: CPL qualified debug store", "VMX: Virtual Machine eXtensions",
        "SMX: Safer Mode Extensions (LaGrande) (GETSEC instruction)", "EIST: Enhanced SpeedStep",
        "TM2: Thermal Monitor 2", "SSSE3: Supplemental SSE3 instructions", "CNXTID: L1 Context ID",
        "SDBG: Silicon Debug Interface",
        "FMA: Fused multiply-add (FMA3)", "CMPXCHG16B: CMPXCHG16B instruction",
        "xTPR: Can disable sending task priority messages", "PDCM: Perfmon & debug capability",
        "PCID: Process context identifiers",
        "DCA: Direct cache access for DMA writes", "SSE41: SSE4.1 instructions", "SSE42: SSE4.2 instructions",
        "x2APIC: enhanced APIC", "MOVBE: MOVBE instruction (big-endian)", "POPCNT: POPCNT instruction",
        "TSCDeadline: APIC implements one-shot operation using a TSC deadline value",
        "AESNI: AES instruction set",
        "XSAVE: Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions",
        "OSXSAVE: XSAVE enabled by OS", "AVX: Advanced Vector Extensions (256-bit SIMD)",
        "F16C: Floating-point conversion instructions to/from FP16 format", "RDRND: on-chip random number generator",
        "HYPRVSR: Hypervisor present",
        "FPU: Onboard x87 FPU", "VME: Virtual 8086 mode extensions (such as VIF, VIP, PVI)",
        "DE: Debugging extensions (CR4 bit 3)", "PSE: Page Size Extension (4 MB pages)",
        "TSC: Time Stamp Counter and RDTSC instruction", "MSR: 	Model-specific registers and RDMSR/WRMSR instructions",
        "PAE: 	Physical Address Extension", "MCE: Machine Check Exception",
        "CX8: CMPXCHG8B (compare-and-swap) instruction", "APIC:Onboard Advanced Programmable Interrupt Controller",
        "SEP: SYSENTER and SYSEXIT fast system call instructions", "MTRR: Memory Type Range Registers",
        "PGE: Page Global Enable bit in CR4", "MCA: Machine check architecture",
        "CMOV:Conditional move: CMOV, FCMOV and FCOMI instructions", "PAT: Page Attribute Table",
        "PSE36: 	36-bit page size extension", "PSN: Processor Serial Number supported and enabled",
        "CLFSH: CLFLUSH cache line flush instruction (SSE2)", "DS: Debug store: save trace of executed jumps",
        "ACPI: Onboard thermal control MSRs for ACPI",
        "MMX: MMX instructions (64-bit SIMD)", "FXSR: FXSAVE, FXRSTOR instructions, CR4 bit 9",
        "SSE: Streaming SIMD Extensions instructions (128-bit SIMD)", "SSE2: SSE2 instructions",
        "SS: CPU cache implements self-snoop", "HTT: Max APIC IDs reserved field is Valid",
        "TM: Thermal monitor automatically limits temperature", "IA64: IA64 processor emulating x86",
        "PBE: Pending Break Enable (PBE# pin) wakeup capability", "FSGSBASE: Access to base of %fs and %gs",
        "SGX: Software Guard Extensions", "BMI: Bit Manipulation Instruction Set 1", "HLE: TSX Hardware Lock Elision",
        "AVX2: Advanced Vector Extensions 2", "FDPXO: x87 FPU data pointer register updated on exceptions only",
        "SMEP: Supervisor Mode Execution Prevention", "BMI2: Bit Manipulation Instruction Set 2",
        "ENH_MOVSB: Enhanced REP MOVSB/STOSB", "INVPCID: INVPCID instruction",
        "RTM: TSX Restricted Transactional Memory", "MPX: Intel MPX (Memory Protection Extensions)",
        "AVX512F: AVX-512 Foundation", "AVX512DQ: AVX-512 Doubleword and Quadword Instructions",
        "RDSEED: RDSEED instruction", "ADX: Intel ADX (Multi-Precision Add-Carry Instruction Extensions)",
        "SMAP: Supervisor Mode Access Prevention", "AVX512IFMA: AVX-512 Integer Fused Multiply-Add Instructions",
        "CLFLUSHOPT: CLFLUSHOPT instruction", "CLWB: Cache line writeback instruction", "PT: Intel Processor Trace",
        "AVX512PF: AVX-512 Prefetch Instructions", "AVX512ER: AVX-512 Exponential and Reciprocal Instructions",
        "AVX512CD: AVX-512 Conflict Detection Instructions", "SHA: SHA-1 and SHA-256 extensions",
        "AVX512BW: AVX-512 Byte and Word Instructions", "AVX512VL: AVX-512 Vector Length Extensions",
        "PREFTCHWT1: PREFETCHWT1 instruction",
        "AVX512VBMI: AVX-512 Vector Bit Manipulation Instructions", "UMIP: User-Mode Instruction Prevention",
        "PKU: Memory Protection Keys for User-mode pages", "OSPKE: PKU enabled by OS",
        "WAITPKG: Timed pause and user-level monitor/wait instructions (TPAUSE, UMONITOR, UMWAIT)",
        "AVX512VBMI2: AVX-512 Vector Bit Manipulation Instructions 2",
        "SHSTK: Control flow enforcement (CET): shadow stack", "GFNI: Galois Field instructions",
        "VAES: Vector AES instruction set (VEX-256/EVEX)", "VPCLMULQDQ: CLMUL instruction set (VEX-256/EVEX)",
        "AVX512VNNI: AVX-512 Vector Neural Network Instructions", "AVX512BITALG: AVX-512 BITALG instructions",
        "TMEM: Total Memory Encryption MSRs available",
        "AVX512VPOPCNTDQ: AVX-512 Vector Population Count Double and Quad-word",
        "IA57: 5-level paging (57 address bits)", "RDPID: Read Processor ID instruction and IA32_TSC_AUX MSR",
        "KL: AES Key Locker", "BLD: Bus lock debug exceptions", "CLDEMOTE: Cache line demote instruction",
        "MOVDIRI: MOVDIRI instruction", "MOVDIR64B: MOVDIR64B (64-byte direct store) instruction",
        "ENQCMD: Enqueue Stores and EMQCMD/EMQCMDS instructions", "SGXLC: SGX Launch Configuration",
        "PKS: Protection Keys for supervisor-mode pages", "SGXKEYS: Attestation Services for Intel SGX",
        "AVX5124VNNIW: AVX-512 4-register Neural Network Instructions",
        "AVX5124FMAPS: AVX-512 4-register Multiply Accumulation Single precision", "FSRM: Fast Short REP MOV",
        "UINTR: User Inter-processor Interrupts",
        "AVX512VP2INTERSECT: AVX-512 vector intersection instructions on 32/64-bit integers",
        "SRBDSCTRL: Special Register Buffer Data Sampling Mitigations",
        "MDCLEAR: VERW instruction clears CPU buffers", "RTMAA (rtm-always-abort): All TSX transactions are aborted",
        "RTMFA (rtm-force-abort): TSX_FORCE_ABORT (MSR 0x10f) is available",
        "SERIALIZE: SERIALIZE instruction", "HYBRID: Hybrid processor (Mixture of CPU types in processor topology)",
        "TSXLDTRK: TSX load address tracking suspend/resume instructions (TSUSLDTRK and TRESLDTRK)",
        "PCONFIG: Platform configuration (Memory Encryption Technologies Instructions)",
        "LBR: Architectural Last Branch Records",
        "IBT: Control flow enforcement (CET): indirect branch tracking",
        "AMXBF16: AMX tile computation on bfloat16 numbers",
        "AVX512FP16: AVX-512 half-precision floating-point arithmetic instructions",
        "AMXTILE: AMX tile load/store instructions", "AMXINT8: AMX tile computation on 8-bit integers",
        "IBRRS: Indirect Branch Restricted Speculation (IBRS) and Indirect Branch Prediction Barrier (IBPB)",
        "STIBP: Single Thread Indirect Branch Predictor", "L1D_FLUSH: IA32_FLUSH_CMD MSR",
        "IA32_ARCH_CAPABILITIES: IA32_ARCH_CAPABILITIES MSR (lists speculative side channel mitigations)",
        "IA32_CORE_CAPABILITIES: IA32_CORE_CAPABILITIES MSR (lists model-specific core capabilities)",
        "SSBD: Speculative Store Bypass Disable",
        "SHA512: SHA-512 extensions", "SM3: SM3 hash extensions", "SM4: SM4 cipher extensions",
        "RAOINT: Remote Atomic Operations on integers: AADD, AAND, AOR, AXOR instructions",
        "AVXVNNI: AVX Vector Neural Network Instructions (VNNI) (VEX encoded)",
        "AVX512BF16: AVX-512 instructions for bfloat16 numbers",
        "CMPCCXADD: CMPccXADD instructions", "FRED: Flexible Return and Event Delivery", "LKGS: LKGS Instruction",
        "WRMSRNS: WRMSRNS instruction (non-serializing write to MSRs)", "NMISRC: NMI source reporting",
        "AMXFP16: AMX instructions for FP16 numbers",
        "HRESET: HRESET instruction, IA32_HRESET_ENABLE (17DAh) MSR, and Processor History Reset Leaf (EAX=20h)",
        "AVXIFMA: AVX IFMA instructions",
        "MSRLIST: RDMSRLIST and WRMSRLIST instructions, and the IA32_BARRIER (02Fh) MSR",
        "MOVRS: MOVRS and PREFETCHRST2 instructions supported (memory read/prefetch with read-shared hint)",
        "PBNDKB: Total Storage Encryption: PBNDKB instruction and TSE_CAPABILITY (9F1h) MSR.",
        "AVXVNNIINT8: AVX VNNI INT8 instructions",
        "AVXNECONVERT: AVX no-exception FP conversion instructions (bfloat16↔FP32 and FP16→FP32)",
        "AMXCOMPLEX: AMX support for \"complex\" tiles (TCMMIMFP16PS and TCMMRLFP16PS)",
        "AVXVNNIINT16: AVX VNNI INT16 instructions",
        "PREFETCHI: Instruction-cache prefetch instructions (PREFETCHIT0 and PREFETCHIT1)",
        "USERMSR: User-mode MSR access instructions (URDMSR and UWRMSR)", "AVX10: AVX10 Converged Vector ISA",
        "APXF: Advanced Performance Extensions, Foundation",
        "XSAVEOPT: XSAVEOPT instruction: save state-components that have been modified since last XRSTOR",
        "XSAVEC: XSAVEC instruction: save/restore state with compaction",
        "XSAVES: XSAVES and XRSTORS instructions and IA32_XSS MSR",
        "XSAVEXFD: XFD (Extended Feature Disable) supported", "PTWRITE: PTWRITE instruction supported",
        "AESKLE: AES \"Key Locker\" Instructions enabled", "WIDEKL: AES \"Wide Key Locker\" Instructions",
        "AMXFP8: AMX float8 support",
        "AMX_TRANSPOSE: AMX Transposition instruction support", "AMX_TF32: AMX tf32/fp19 support",
        "AMX_AVX512: AMX-AVX512 support", "AMX_MOVRS: AMX-MOVRS support",
        "AVX10_256: 256-bit vector support is present", "AVX10_512: 512-bit vector support is present",
        "LAHF_LM: LAHF/SAHF in long mode", "ABM: Advanced bit manipulation (LZCNT and POPCNT)",
        "SSE4a: SSE4a instructions",
        "PRFCHW: PREFETCH and PREFETCHW instructions", "XOP: XOP instruction set", "LWP: Light Weight Profiling",
        "FMA4: 4-operand fused multiply-add instructions", "TBM: Trailing Bit Manipulation",
        "MWAITX: MONITORX and MWAITX instructions", "MMXEXT: Extended MMX", "LM: Long mode",
        "3DNOWP: Extended 3DNow!", "3DNOW: 3DNow!", "CLZERO: CLZERO instruction", "RDPRU: RDPRU instruction",
        "WBNOINVD: WBNOINVD instruction",
    };

    const bool* feature_values = (const bool*)feats;

    printf("\nAvailable CPU Features:\n");
    for (size_t i = 0; i < sizeof(feature_names) / sizeof(feature_names[0]); ++i) {
        if (feature_values[i]) {
            printf("- %s\n", feature_names[i]);
        }
    }
}

int main() {
    if (!check_cpuid()) {
        fputs("CPUID instruction is not supported by your cpu.\n", stderr);
        return 1;
    }

    uint32_t registers[4] = {0}; // Registers: EAX, EBX, ECX, EDX
    cpu_basic_info basic_info;

    // Query the basic CPUID information
    cpuid(0, registers);

    if ((basic_info.highest_leaf = registers[0])) {
        // Check for the CPU vendor
        memcpy(basic_info.vendor, &registers[1], 4);
        memcpy(basic_info.vendor + 4, &registers[3], 4);
        memcpy(basic_info.vendor + 8, &registers[2], 4);
        basic_info.vendor[12] = '\0';

        // Highest extended function calling parameter
        cpuid(0x80000000, registers);
        basic_info.highest_extended_leaf = registers[0];

        // Check for the CPU brand string
        if (basic_info.highest_extended_leaf >= 0x80000004) {
            cpuid(0x80000002, registers);
            memcpy(basic_info.brand, registers, 16);
            cpuid(0x80000003, registers);
            memcpy(basic_info.brand + 16, registers, 16);
            cpuid(0x80000004, registers);
            memcpy(basic_info.brand + 32, registers, 16);
            basic_info.brand[48] = '\0';
        }

        // Check for the CPU family, model, and stepping
        cpuid(1, registers);
        basic_info.family = ((registers[0] >> 8) & 0xF) + ((registers[0] >> 20) & 0xFF);
        basic_info.model = ((registers[0] >> 4) & 0xF) + ((registers[0] >> 12) & 0xF0);
        basic_info.stepping = registers[0] & 0xF;

        print_basic_info(&basic_info);

        // Check for standard feature flags (CPUID Leaf 1)
        cpu_features features = {
            // %ecx flags
            .SSE3 = registers[2] & b_SSE3,
            .PCLMULQDQ = registers[2] & b_PCLMULQDQ,
            .DTES64 = registers[2] & b_DTES64,
            .MONITOR = registers[2] & b_MONITOR,
            .DSCPL = registers[2] & b_DSCPL,
            .VMX = registers[2] & b_VMX,
            .SMX = registers[2] & b_SMX,
            .EIST = registers[2] & b_EIST,
            .TM2 = registers[2] & b_TM2,
            .SSSE3 = registers[2] & b_SSSE3,
            .CNXTID = registers[2] & b_CNXTID,
            .SDBG = registers[2] & b_SDBG,
            .FMA = registers[2] & b_FMA,
            .CMPXCHG16B = registers[2] & b_CMPXCHG16B,
            .xTPR = registers[2] & b_xTPR,
            .PDCM = registers[2] & b_PDCM,
            .PCID = registers[2] & b_PCID,
            .DCA = registers[2] & b_DCA,
            .SSE41 = registers[2] & b_SSE41,
            .SSE42 = registers[2] & b_SSE42,
            .x2APIC = registers[2] & b_x2APIC,
            .MOVBE = registers[2] & b_MOVBE,
            .POPCNT = registers[2] & b_POPCNT,
            .TSCDeadline = registers[2] & b_TSCDeadline,
            .AESNI = registers[2] & b_AESNI,
            .XSAVE = registers[2] & b_XSAVE,
            .OSXSAVE = registers[2] & b_OSXSAVE,
            .AVX = registers[2] & b_AVX,
            .F16C = registers[2] & b_F16C,
            .RDRND = registers[2] & b_RDRND,
            .HYPRVSR = registers[2] & b_HYPRVSR,

            // %edx flags
            .FPU = registers[3] & b_FPU,
            .VME = registers[3] & b_VME,
            .DE = registers[3] & b_DE,
            .PSE = registers[3] & b_PSE,
            .TSC = registers[3] & b_TSC,
            .MSR = registers[3] & b_MSR,
            .PAE = registers[3] & b_PAE,
            .MCE = registers[3] & b_MCE,
            .CX8 = registers[3] & b_CX8,
            .APIC = registers[3] & b_APIC,
            .SEP = registers[3] & b_SEP,
            .MTRR = registers[3] & b_MTRR,
            .PGE = registers[3] & b_PGE,
            .MCA = registers[3] & b_MCA,
            .CMOV = registers[3] & b_CMOV,
            .PAT = registers[3] & b_PAT,
            .PSE36 = registers[3] & b_PSE36,
            .PSN = registers[3] & b_PSN,
            .CLFSH = registers[3] & b_CLFSH,
            .DS = registers[3] & b_DS,
            .ACPI = registers[3] & b_ACPI,
            .MMX = registers[3] & b_MMX,
            .FXSR = registers[3] & b_FXSR,
            .SSE = registers[3] & b_SSE,
            .SSE2 = registers[3] & b_SSE2,
            .SS = registers[3] & b_SS,
            .HTT = registers[3] & b_HTT,
            .TM = registers[3] & b_TM,
            .IA64 = registers[3] & b_IA64,
            .PBE = registers[3] & b_PBE,
        };

        // Check for extended feature flags (CPUID Leaf 7)
        if (basic_info.highest_leaf >= 7) {
            // sub-leaf 0
            cpuid_extended(7, 0, registers);

            // %ebx flags
            features.FSGSBASE = registers[1] & b_FSGSBASE;
            features.SGX = registers[1] & b_SGX;
            features.BMI = registers[1] & b_BMI;
            features.HLE = registers[1] & b_HLE;
            features.FDPXO = registers[1] & b_FDPXO;
            features.AVX2 = registers[1] & b_AVX2;
            features.SMEP = registers[1] & b_SMEP;
            features.BMI2 = registers[1] & b_BMI2;
            features.ENH_MOVSB = registers[1] & b_ENH_MOVSB;
            features.INVPCID = registers[1] & b_INVPCID;
            features.RTM = registers[1] & b_RTM;
            features.MPX = registers[1] & b_MPX;
            features.AVX512F = registers[1] & b_AVX512F;
            features.AVX512DQ = registers[1] & b_AVX512DQ;
            features.RDSEED = registers[1] & b_RDSEED;
            features.ADX = registers[1] & b_ADX;
            features.SMAP = registers[1] & b_SMAP;
            features.AVX512IFMA = registers[1] & b_AVX512IFMA;
            features.CLFLUSHOPT = registers[1] & b_CLFLUSHOPT;
            features.CLWB = registers[1] & b_CLWB;
            features.PT = registers[1] & b_PT;
            features.AVX512PF = registers[1] & b_AVX512PF;
            features.AVX512ER = registers[1] & b_AVX512ER;
            features.AVX512CD = registers[1] & b_AVX512CD;
            features.SHA = registers[1] & b_SHA;
            features.AVX512BW = registers[1] & b_AVX512BW;
            features.AVX512VL = registers[1] & b_AVX512VL;

            // %ecx flags
            features.PREFTCHWT1 = registers[2] & b_PREFTCHWT1;
            features.AVX512VBMI = registers[2] & b_AVX512VBMI;
            features.UMIP = registers[2] & b_UMIP;
            features.PKU = registers[2] & b_PKU;
            features.OSPKE = registers[2] & b_OSPKE;
            features.WAITPKG = registers[2] & b_WAITPKG;
            features.AVX512VBMI2 = registers[2] & b_AVX512VBMI2;
            features.SHSTK = registers[2] & b_SHSTK;
            features.GFNI = registers[2] & b_GFNI;
            features.VAES = registers[2] & b_VAES;
            features.VPCLMULQDQ = registers[2] & b_VPCLMULQDQ;
            features.AVX512VNNI = registers[2] & b_AVX512VNNI;
            features.AVX512BITALG = registers[2] & b_AVX512BITALG;
            features.TMEM = registers[2] & b_TMEM;
            features.AVX512VPOPCNTDQ = registers[2] & b_AVX512VPOPCNTDQ;
            features.IA57 = registers[2] & b_IA57;
            features.RDPID = registers[2] & b_RDPID;
            features.KL = registers[2] & b_KL;
            features.BLD = registers[2] & b_BLD;
            features.CLDEMOTE = registers[2] & b_CLDEMOTE;
            features.MOVDIRI = registers[2] & b_MOVDIRI;
            features.MOVDIR64B = registers[2] & b_MOVDIR64B;
            features.ENQCMD = registers[2] & b_ENQCMD;
            features.SGXLC = registers[2] & b_SGXLC;
            features.PKS = registers[2] & b_PKS;

            // %edx flags
            features.SGXKEYS = registers[3] & b_SGXKEYS;
            features.AVX5124VNNIW = registers[3] & b_AVX5124VNNIW;
            features.AVX5124FMAPS = registers[3] & b_AVX5124FMAPS;
            features.FSRM = registers[3] & b_FSRM;
            features.UINTR = registers[3] & b_UINTR;
            features.AVX512VP2INTERSECT = registers[3] & b_AVX512VP2INTERSECT;
            features.SRBDSCTRL = registers[3] & b_SRBDSCTRL;
            features.MDCLEAR = registers[3] & b_MDCLEAR;
            features.RTMAA = registers[3] & b_RTMAA;
            features.RTMFA = registers[3] & b_RTMFA;
            features.SERIALIZE = registers[3] & b_SERIALIZE;
            features.HYBRID = registers[3] & b_HYBRID;
            features.TSXLDTRK = registers[3] & b_TSXLDTRK;
            features.PCONFIG = registers[3] & b_PCONFIG;
            features.LBR = registers[3] & b_LBR;
            features.IBT = registers[3] & b_IBT;
            features.AMXBF16 = registers[3] & b_AMXBF16;
            features.AVX512FP16 = registers[3] & b_AVX512FP16;
            features.AMXTILE = registers[3] & b_AMXTILE;
            features.AMXINT8 = registers[3] & b_AMXINT8;
            features.IBRRS = registers[3] & b_IBRRS;
            features.STIBP = registers[3] & b_STIBP;
            features.L1D_FLUSH = registers[3] & b_L1D_FLUSH;
            features.IA32_ARCH_CAPABILITIES = registers[3] & b_IA32_ARCH_CAPABILITIES;
            features.IA32_CORE_CAPABILITIES = registers[3] & b_IA32_CORE_CAPABILITIES;
            features.SSBD = registers[3] & b_SSBD;

            // sub-leaf 1
            cpuid_extended(7, 1, registers);

            // %eax flags
            features.SHA512 = registers[0] & b_SHA512;
            features.SM3 = registers[0] & b_SM3;
            features.SM4 = registers[0] & b_SM4;
            features.RAOINT = registers[0] & b_RAOINT;
            features.AVXVNNI = registers[0] & b_AVXVNNI;
            features.AVX512BF16 = registers[0] & b_AVX512BF16;
            features.CMPCCXADD = registers[0] & b_CMPCCXADD;
            features.FRED = registers[0] & b_FRED;
            features.LKGS = registers[0] & b_LKGS;
            features.WRMSRNS = registers[0] & b_WRMSRNS;
            features.NMISRC = registers[0] & b_NMISRC;
            features.AMXFP16 = registers[0] & b_AMXFP16;
            features.HRESET = registers[0] & b_HRESET;
            features.AVXIFMA = registers[0] & b_AVXIFMA;
            features.MSRLIST = registers[0] & b_MSRLIST;
            features.MOVRS = registers[0] & b_MOVRS;

            // %ebx flags
            features.PBNDKB = registers[1] & b_PBNDKB;

            // %edx flags
            features.AVXVNNIINT8 = registers[3] & b_AVXVNNIINT8;
            features.AVXNECONVERT = registers[3] & b_AVXNECONVERT;
            features.AMXCOMPLEX = registers[3] & b_AMXCOMPLEX;
            features.AVXVNNIINT16 = registers[3] & b_AVXVNNIINT16;
            features.PREFETCHI = registers[3] & b_PREFETCHI;
            features.USERMSR = registers[3] & b_USERMSR;
            features.AVX10 = registers[3] & b_AVX10;
            features.APXF = registers[3] & b_APXF;
        }

        // Leaf 13
        if (basic_info.highest_leaf >= 13) {
            // sub-leaf 1
            cpuid_extended(13, 1, registers);

            // %eax flags
            features.XSAVEOPT = registers[0] & b_XSAVEOPT;
            features.XSAVEC = registers[0] & b_XSAVEC;
            features.XSAVES = registers[0] & b_XSAVES;
            features.XSAVEXFD = registers[0] & b_XSAVEXFD;
        }

        // Leaf 0x14
        if (basic_info.highest_leaf >= 0x14) {
            // sub-leaf 0
            cpuid_extended(0x14, 0, registers);

            // %ebx flags
            features.PTWRITE = registers[1] & b_PTWRITE;
        }

        // Keylocker leaf (leaf 0x19)
        if (basic_info.highest_extended_leaf >= 0x19) {
            cpuid(0x19, registers);

            // %eax flags
            features.AESKLE = registers[0] & b_AESKLE;
            features.WIDEKL = registers[0] & b_WIDEKL;
        }

        // AMX sub-leaf
        if (basic_info.highest_extended_leaf >= 0x1e) {
            // sub-leaf 1
            cpuid_extended(0x1e, 1, registers);

            // %eax flags
            features.AMXFP8 = registers[0] & b_AMXFP8;
            features.AMX_TRANSPOSE = registers[0] & b_AMX_TRANSPOSE;
            features.AMX_TF32 = registers[0] & b_AMX_TF32;
            features.AMX_AVX512 = registers[0] & b_AMX_AVX512;
            features.AMX_MOVRS = registers[0] & b_AMX_MOVRS;
        }

        // Leaf 0x24
        if (basic_info.highest_extended_leaf >= 0x24) {
            cpuid_extended(0x24, 0, registers);

            // %ebx flags
            features.AVX10_256 = registers[1] & b_AVX10_256;
            features.AVX10_512 = registers[1] & b_AVX10_512;
        }

        // Leaf 0x80000001
        if (basic_info.highest_extended_leaf >= 0x80000001) {
            cpuid(0x80000001, registers);

            // %ecx flags
            features.LAHF_LM = registers[2] & b_LAHF_LM;
            features.ABM = registers[2] & b_ABM;
            features.SSE4a = registers[2] & b_SSE4a;
            features.PRFCHW = registers[2] & b_PRFCHW;
            features.XOP = registers[2] & b_XOP;
            features.LWP = registers[2] & b_LWP;
            features.FMA4 = registers[2] & b_FMA4;
            features.TBM = registers[2] & b_TBM;
            features.MWAITX = registers[2] & b_MWAITX;

            // %edx flags
            features.MMXEXT = registers[3] & b_MMXEXT;
            features.LM = registers[3] & b_LM;
            features.x3DNOWP = registers[3] & b_3DNOWP;
            features.x3DNOW = registers[3] & b_3DNOW;
        }

        // Leaf 0x80000008
        if (basic_info.highest_extended_leaf >= 0x80000008) {
            cpuid(0x80000008, registers);

            // %ebx flags
            features.CLZERO = registers[1] & b_CLZERO;
            features.RDPRU = registers[1] & b_RDPRU;
            features.WBNOINVD = registers[1] & b_WBNOINVD;
        }

        print_available_features(&features);
        return 0;
    }
    fputs("CPUID instruction failed to return any information.\n", stderr);

    return 1;
}
