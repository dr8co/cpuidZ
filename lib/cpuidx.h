#pragma once
#ifndef CPUIDX_H
#define CPUIDX_H

#if defined(__cplusplus) && __cplusplus
extern "C" {
#define CPUIDX_LANG_CPP 1
#define CPUIDX_CONSTEXPR_AVAILABLE 1
#define CPUIDX_BOOL_AVAILABLE 1
#endif // defined(__cplusplus) && __cplusplus

// C23 support for constexpr & bool.
// The full C23 standard should be 202311L, but GCC has constexpr & bool at 202000L
#if __STDC_VERSION__ >= 202000L
#ifdef __clang__
#if __clang_major__ >= 18
#ifndef CPUIDX_BOOL_AVAILABLE
#define CPUIDX_BOOL_AVAILABLE 1
#endif // !CPUIDX_BOOL_AVAILABLE
#endif // __clang_major__ >= 18
#if __clang_major__ >= 19 // Clang supports C23 constexpr from version 19
#ifndef CPUIDX_CONSTEXPR_AVAILABLE
#define CPUIDX_CONSTEXPR_AVAILABLE 1
#endif // !CPUIDX_CONSTEXPR_AVAILABLE
#endif // __clang_major__ >= 19
#elif defined(__GNUC__) // __clang__
#if __GNUC__ >= 13
#ifndef CPUIDX_CONSTEXPR_AVAILABLE
#define CPUIDX_CONSTEXPR_AVAILABLE 1
#endif // !CPUIDX_CONSTEXPR_AVAILABLE
#ifndef CPUIDX_BOOL_AVAILABLE
#define CPUIDX_BOOL_AVAILABLE 1
#endif // !CPUIDX_BOOL_AVAILABLE
#endif // __GNUC__ >= 13
#endif // defined(__GNUC__)
#endif // __STDC_VERSION__ >= 202000L

#include <stdint.h>
#ifndef CPUIDX_BOOL_AVAILABLE
#include <stdbool.h>
#endif

/**
* @brief Structure to hold basic CPU information.
*/
struct cpu_basic_info {
    char vendor[13]; /**< Vendor name */
    char brand[49]; /**< Brand name */
    uint32_t family; /**< Family */
    uint32_t model; /**< Model */
    uint32_t stepping; /**< Stepping ID */
    uint32_t highest_basic_leaf; /**< Highest basic feature leaf */
    uint32_t highest_extended_leaf; /**< Highest extended feature leaf */
};

/**
* @brief Structure to hold CPU features.
*/
struct cpu_features {
    bool SSE3; /**< Prescott New Instructions - PNI */
    bool PCLMULQDQ; /**< carry-less multiply */
    bool DTES64; /**< 64-bit debug store */
    bool MONITOR; /**< MONITOR and MWAIT instructions (PNI) */
    bool DSCPL; /**< CPL qualified debug store */
    bool VMX; /**< Virtual Machine eXtensions */
    bool SMX; /**< Safer Mode Extensions (LaGrande) (GETSEC instruction) */
    bool EIST; /**< Enhanced SpeedStep */
    bool TM2; /**< Thermal Monitor 2 */
    bool SSSE3; /**< Supplemental SSE3 instructions */
    bool CNXTID; /**< L1 Context ID */
    bool SDBG; /**< Silicon Debug Interface */
    bool FMA; /**< Fused multiply-add (FMA3) */
    bool CMPXCHG16B; /**< CMPXCHG16B instruction */
    bool xTPR; /**< Can disable sending task priority messages */
    bool PDCM; /**< Perfmon & debug capability */
    bool PCID; /**< Process context identifiers */
    bool DCA; /**< Direct cache access for DMA writes */
    bool SSE41; /**< SSE4.1 instructions */
    bool SSE42; /**< SSE4.2 instructions */
    bool x2APIC; /**< enhanced APIC */
    bool MOVBE; /**< MOVBE instruction (big-endian) */
    bool POPCNT; /**< POPCNT instruction */
    bool TSCDeadline; /**< APIC implements one-shot operation using a TSC deadline value */
    bool AESNI; /**< AES instruction set */
    bool XSAVE; /**< Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions */
    bool OSXSAVE; /**< XSAVE enabled by OS */
    bool AVX; /**< Advanced Vector Extensions (256-bit SIMD) */
    bool F16C; /**< Floating-point conversion instructions to/from FP16 format */
    bool RDRND; /**< on-chip random number generator */
    bool HYPRVSR; /**< Hypervisor present */
    bool FPU; /**< Onboard x87 FPU */
    bool VME; /**< Virtual 8086 mode extensions (such as VIF, VIP, PVI) */
    bool DE; /**< Debugging extensions (CR4 bit 3) */
    bool PSE; /**< Page Size Extension (4 MB pages) */
    bool TSC; /**< Time Stamp Counter and RDTSC instruction */
    bool MSR; /**< Model-specific registers and RDMSR/WRMSR instructions */
    bool PAE; /**< Physical Address Extension */
    bool MCE; /**< Machine Check Exception */
    bool CX8; /**< CMPXCHG8B (compare-and-swap) instruction */
    bool APIC; /**< Onboard Advanced Programmable Interrupt Controller */
    bool SEP; /**< SYSENTER and SYSEXIT fast system call instructions */
    bool MTRR; /**< Memory Type Range Registers */
    bool PGE; /**< Page Global Enable bit in CR4 */
    bool MCA; /**< Machine check architecture */
    bool CMOV; /**< Conditional move: CMOV, FCMOV and FCOMI instructions */
    bool PAT; /**< Page Attribute Table */
    bool PSE36; /**< 36-bit page size extension */
    bool PSN; /**< Processor Serial Number supported and enabled */
    bool CLFSH; /**< CLFLUSH cache line flush instruction (SSE2) */
    bool DS; /**< Debug store: save trace of executed jumps */
    bool ACPI; /**< Onboard thermal control MSRs for ACPI */
    bool MMX; /**< MMX instructions (64-bit SIMD) */
    bool FXSR; /**< FXSAVE, FXRSTOR instructions, CR4 bit 9 */
    bool SSE; /**< Streaming SIMD Extensions instructions (128-bit SIMD) */
    bool SSE2; /**< SSE2 instructions */
    bool SS; /**< CPU cache implements self-snoop */
    bool HTT; /**< Max APIC IDs reserved field is Valid */
    bool TM; /**< Thermal monitor automatically limits temperature */
    bool IA64; /**< IA64 processor emulating x86 */
    bool PBE; /**< Pending Break Enable (PBE# pin) wakeup capability */
    bool FSGSBASE; /**< Access to base of %fs and %gs */
    bool SGX; /**< Software Guard Extensions */
    bool BMI; /**< Bit Manipulation Instruction Set 1 */
    bool HLE; /**< TSX Hardware Lock Elision */
    bool AVX2; /**< Advanced Vector Extensions 2 */
    bool FDPXO; /**< x87 FPU data pointer register updated on exceptions only */
    bool SMEP; /**< Supervisor Mode Execution Prevention */
    bool BMI2; /**< Bit Manipulation Instruction Set 2 */
    bool ENH_MOVSB; /**< Enhanced REP MOVSB/STOSB */
    bool INVPCID; /**< INVPCID instruction */
    bool RTM; /**< TSX Restricted Transactional Memory */
    bool MPX; /**< Intel MPX (Memory Protection Extensions) */
    bool AVX512F; /**< AVX-512 Foundation */
    bool AVX512DQ; /**< AVX-512 Doubleword and Quadword Instructions */
    bool RDSEED; /**< RDSEED instruction */
    bool ADX; /**< Intel ADX (Multi-Precision Add-Carry Instruction Extensions) */
    bool SMAP; /**< Supervisor Mode Access Prevention */
    bool AVX512IFMA; /**< AVX-512 Integer Fused Multiply-Add Instructions */
    bool CLFLUSHOPT; /**< CLFLUSHOPT instruction */
    bool CLWB; /**< Cache line writeback instruction */
    bool PT; /**< Intel Processor Trace */
    bool AVX512PF; /**< AVX-512 Prefetch Instructions */
    bool AVX512ER; /**< AVX-512 Exponential and Reciprocal Instructions */
    bool AVX512CD; /**< AVX-512 Conflict Detection Instructions */
    bool SHA; /**< SHA-1 and SHA-256 extensions */
    bool AVX512BW; /**< AVX-512 Byte and Word Instructions */
    bool AVX512VL; /**< AVX-512 Vector Length Extensions */
    bool PREFTCHWT1; /**< PREFETCHWT1 instruction */
    bool AVX512VBMI; /**< AVX-512 Vector Bit Manipulation Instructions */
    bool UMIP; /**< User-Mode Instruction Prevention */
    bool PKU; /**< Memory Protection Keys for User-mode pages */
    bool OSPKE; /**< PKU enabled by OS */
    bool WAITPKG; /**< Timed pause and user-level monitor/wait instructions (TPAUSE, UMONITOR, UMWAIT) */
    bool AVX512VBMI2; /**< AVX-512 Vector Bit Manipulation Instructions 2 */
    bool SHSTK; /**< Control flow enforcement (CET): shadow stack */
    bool GFNI; /**< Galois Field instructions */
    bool VAES; /**< Vector AES instruction set (VEX-256/EVEX) */
    bool VPCLMULQDQ; /**< CLMUL instruction set (VEX-256/EVEX) */
    bool AVX512VNNI; /**< AVX-512 Vector Neural Network Instructions */
    bool AVX512BITALG; /**< AVX-512 BITALG instructions */
    bool TMEM; /**< Total Memory Encryption MSRs available */
    bool AVX512VPOPCNTDQ; /**< AVX-512 Vector Population Count Double and Quad-word */
    bool IA57; /**< 5-level paging (57 address bits) */
    bool RDPID; /**< Read Processor ID instruction and IA32_TSC_AUX MSR */
    bool KL; /**< AES Key Locker */
    bool BLD; /**< Bus lock debug exceptions */
    bool CLDEMOTE; /**< Cache line demote instruction */
    bool MOVDIRI; /**< MOVDIRI instruction */
    bool MOVDIR64B; /**< MOVDIR64B (64-byte direct store) instruction */
    bool ENQCMD; /**< Enqueue Stores and EMQCMD/EMQCMDS instructions */
    bool SGXLC; /**< SGX Launch Configuration */
    bool PKS; /**< Protection Keys for supervisor-mode pages */
    bool SGXKEYS; /**< Attestation Services for Intel SGX */
    bool AVX5124VNNIW; /**< AVX-512 4-register Neural Network Instructions */
    bool AVX5124FMAPS; /**< AVX-512 4-register Multiply Accumulation Single precision */
    bool FSRM; /**< Fast Short REP MOV */
    bool UINTR; /**< User Inter-processor Interrupts */
    bool AVX512VP2INTERSECT; /**< AVX-512 vector intersection instructions on 32/64-bit integers */
    bool SRBDSCTRL; /**< Special Register Buffer Data Sampling Mitigations */
    bool MDCLEAR; /**< VERW instruction clears CPU buffers */
    bool RTMAA; /**< rtm-always-abort: All TSX transactions are aborted */
    bool RTMFA; /**< rtm-force-abort: TSX_FORCE_ABORT */
    bool SERIALIZE; /**< SERIALIZE instruction */
    bool HYBRID; /**< Hybrid processor topology */
    bool TSXLDTRK; /**< TSX load address tracking suspend/resume instructions */
    bool PCONFIG; /**< Platform Configuration */
    bool LBR; /**< Architectural Last Branch Record */
    bool IBT; /**< Indirect Branch Tracking */
    bool AMXBF16; /**< AMX BF16 instructions */
    bool AVX512FP16; /**< AVX-512 FP16 instructions */
    bool AMXTILE; /**< AMX Tile instructions */
    bool AMXINT8; /**< AMX Int8 instructions */
    bool IBRRS; /**< Indirect Branch Restricted Speculation */
    bool STIBP; /**< Single Thread Indirect Branch Predictors */
    bool L1D_FLUSH; /**< IA32_FLUSH_CMD MSR */
    bool IA32_ARCH_CAPABILITIES; /**< IA32_ARCH_CAPABILITIES MSR */
    bool IA32_CORE_CAPABILITIES; /**< IA32_CORE_CAPABILITIES MSR */
    bool SSBD; /**< Speculative Store Bypass Disable */
    bool SHA512; /**< SHA-512 instructions */
    bool SM3; /**< SM3 hash extensions */
    bool SM4; /**< SM4  cipher extensions */
    bool RAOINT; /**< Remote Atomic Operations on integers */
    bool AVXVNNI; /**< AVX Vector Neural Network Instructions */
    bool AVX512BF16; /**< AVX-512 BF16 instructions */
    bool CMPCCXADD; /**< CMPccXADD instructions */
    bool FRED; /**< Flexible Return and Event Delivery */
    bool LKGS; /**< LKGS Instruction */
    bool WRMSRNS; /**< WRMSRNS instruction */
    bool NMISRC; /**< NMI source */
    bool AMXFP16; /**< AMX FP16 instructions */
    bool HRESET; /**< HRESET instruction */
    bool AVXIFMA; /**< AVX Integer Fused Multiply-Add instructions */
    bool MSRLIST; /**< RDMSRLIST and WRMSRLIST instructions */
    bool MOVRS; /**< MOVRS and PREFETCHRST2 instructions */
    bool PBNDKB; /**< Total Storage Encryption: PBNDKB instruction and TSE_CAPABILITY MSR */
    bool AVXVNNIINT8; /**< AVX Vector Neural Network Instructions with INT8 data */
    bool AVXNECONVERT; /**< AVX no-exception FP conversion instructions */
    bool AMXCOMPLEX; /**< AMX support for 'complex' tiles */
    bool AVXVNNIINT16; /**< AVX Vector Neural Network Instructions with INT16 data */
    bool PREFETCHI; /**< Instruction-cache prefetch instructions (PREFETCHIT0 and PREFETCHIT1) */
    bool USERMSR; /**< User-mode MSR access instructions */
    bool AVX10; /**< AVX10 Converged Vector ISA */
    bool APXF; /**< Advanced Performance Extensions, Foundation */
    bool XSAVEOPT; /**< XSAVEOPT instruction */
    bool XSAVEC; /**< XSAVEC instruction */
    bool XSAVES; /**< XSAVES/XRSTORS instructions */
    bool XSAVEXFD; /**< XFD (Extended Feature Disable) support */
    bool PTWRITE; /**< PTWRITE instruction */
    bool AESKLE; /**< AES 'Key Locker' instructions */
    bool WIDEKL; /**< AES 'Wide Key Locker' instructions */
    bool AMXFP8; /**< AMX float8 support */
    bool AMX_TRANSPOSE; /**< AMX Transposition instruction support */
    bool AMX_TF32; /**< AMX tf32/fp19 support */
    bool AMX_AVX512; /**< AMX-AVX512 support */
    bool AMX_MOVRS; /**< AMX-MOVRS instruction */
    bool AVX10_256; /**< AVX10 256-bit Converged Vector ISA */
    bool AVX10_512; /**< AVX10 512-bit Converged Vector ISA */
    bool LAHF_LM; /**< LAHF/SAHF in long mode */
    bool ABM; /**< Advanced Bit Manipulation (LZCNT and POPCNT) */
    bool SSE4a; /**< SSE4a instructions */
    bool PRFCHW; /**< PREFETCH and PREFETCHW instructions */
    bool XOP; /**< XOP instruction set */
    bool LWP; /**< Light Weight Profiling */
    bool FMA4; /**< 4-operand fused multiply-add instructions */
    bool TBM; /**< Trailing Bit Manipulation */
    bool MWAITX; /**< MWAITX and MONITORX instructions */
    bool MMXEXT; /**< Extended MMX */
    bool LM; /**< Long mode (64-bit support) */
    bool x3DNOWP; /**< Extended 3DNow! */
    bool x3DNOW; /**< 3DNow! */
    bool CLZERO; /**< CLZERO instruction */
    bool RDPRU; /**< RDPRU instruction */
    bool WBNOINVD; /**< WBNOINVD instruction */
};

#ifdef CPUIDX_CONSTEXPR_AVAILABLE
// Features in ecx for CPUID leaf 1
constexpr uint32_t b_SSE3 = 0x00000001;
constexpr uint32_t b_PCLMULQDQ = 0x00000002;
constexpr uint32_t b_DTES64 = 0x00000004;
constexpr uint32_t b_MONITOR = 0x00000008;
constexpr uint32_t b_DSCPL = 0x00000010;
constexpr uint32_t b_VMX = 0x00000020;
constexpr uint32_t b_SMX = 0x00000040;
constexpr uint32_t b_EIST = 0x00000080;
constexpr uint32_t b_TM2 = 0x00000100;
constexpr uint32_t b_SSSE3 = 0x00000200;
constexpr uint32_t b_CNXTID = 0x00000400;
constexpr uint32_t b_SDBG = 0x00000800;
constexpr uint32_t b_FMA = 0x00001000;
constexpr uint32_t b_CMPXCHG16B = 0x00002000;
constexpr uint32_t b_xTPR = 0x00004000;
constexpr uint32_t b_PDCM = 0x00008000;
constexpr uint32_t b_PCID = 0x00020000;
constexpr uint32_t b_DCA = 0x00040000;
constexpr uint32_t b_SSE41 = 0x00080000;
constexpr uint32_t b_SSE42 = 0x00100000;
constexpr uint32_t b_x2APIC = 0x00200000;
constexpr uint32_t b_MOVBE = 0x00400000;
constexpr uint32_t b_POPCNT = 0x00800000;
constexpr uint32_t b_TSCDeadline = 0x01000000;
constexpr uint32_t b_AESNI = 0x02000000;
constexpr uint32_t b_XSAVE = 0x04000000;
constexpr uint32_t b_OSXSAVE = 0x08000000;
constexpr uint32_t b_AVX = 0x10000000;
constexpr uint32_t b_F16C = 0x20000000;
constexpr uint32_t b_RDRND = 0x40000000;
constexpr uint32_t b_HYPRVSR = 0x80000000;

// Features in edx for leaf 1
constexpr uint32_t b_FPU = 0x00000001;
constexpr uint32_t b_VME = 0x00000002;
constexpr uint32_t b_DE = 0x00000004;
constexpr uint32_t b_PSE = 0x00000008;
constexpr uint32_t b_TSC = 0x00000010;
constexpr uint32_t b_MSR = 0x00000020;
constexpr uint32_t b_PAE = 0x00000040;
constexpr uint32_t b_MCE = 0x00000080;
constexpr uint32_t b_CX8 = 0x00000100;
constexpr uint32_t b_APIC = 0x00000200;
constexpr uint32_t b_SEP = 0x00000800;
constexpr uint32_t b_MTRR = 0x00001000;
constexpr uint32_t b_PGE = 0x00002000;
constexpr uint32_t b_MCA = 0x00004000;
constexpr uint32_t b_CMOV = 0x00008000;
constexpr uint32_t b_PAT = 0x00010000;
constexpr uint32_t b_PSE36 = 0x00020000;
constexpr uint32_t b_PSN = 0x00040000;
constexpr uint32_t b_CLFSH = 0x00080000;
constexpr uint32_t b_DS = 0x00200000;
constexpr uint32_t b_ACPI = 0x00400000;
constexpr uint32_t b_MMX = 0x00800000;
constexpr uint32_t b_FXSR = 0x01000000;
constexpr uint32_t b_SSE = 0x02000000;
constexpr uint32_t b_SSE2 = 0x04000000;
constexpr uint32_t b_SS = 0x08000000;
constexpr uint32_t b_HTT = 0x10000000;
constexpr uint32_t b_TM = 0x20000000;
constexpr uint32_t b_IA64 = 0x40000000;
constexpr uint32_t b_PBE = 0x80000000;

// Features in ebx for leaf 7 sub-leaf 0
constexpr uint32_t b_FSGSBASE = 0x00000001;
constexpr uint32_t b_SGX = 0x00000004;
constexpr uint32_t b_BMI = 0x00000008;
constexpr uint32_t b_HLE = 0x00000010;
constexpr uint32_t b_AVX2 = 0x00000020;
constexpr uint32_t b_FDPXO = 0x00000040;
constexpr uint32_t b_SMEP = 0x00000080;
constexpr uint32_t b_BMI2 = 0x00000100;
constexpr uint32_t b_ENH_MOVSB = 0x00000200;
constexpr uint32_t b_INVPCID = 0x00000400;
constexpr uint32_t b_RTM = 0x00000800;
constexpr uint32_t b_MPX = 0x00004000;
constexpr uint32_t b_AVX512F = 0x00010000;
constexpr uint32_t b_AVX512DQ = 0x00020000;
constexpr uint32_t b_RDSEED = 0x00040000;
constexpr uint32_t b_ADX = 0x00080000;
constexpr uint32_t b_SMAP = 0x00100000;
constexpr uint32_t b_AVX512IFMA = 0x00200000;
constexpr uint32_t b_CLFLUSHOPT = 0x00800000;
constexpr uint32_t b_CLWB = 0x01000000;
constexpr uint32_t b_PT = 0x02000000;
constexpr uint32_t b_AVX512PF = 0x04000000;
constexpr uint32_t b_AVX512ER = 0x08000000;
constexpr uint32_t b_AVX512CD = 0x10000000;
constexpr uint32_t b_SHA = 0x20000000;
constexpr uint32_t b_AVX512BW = 0x40000000;
constexpr uint32_t b_AVX512VL = 0x80000000;

// Features in ecx for leaf 7 sub-leaf 0
constexpr uint32_t b_PREFTCHWT1 = 0x00000001;
constexpr uint32_t b_AVX512VBMI = 0x00000002;
constexpr uint32_t b_UMIP = 0x00000004;
constexpr uint32_t b_PKU = 0x00000008;
constexpr uint32_t b_OSPKE = 0x00000010;
constexpr uint32_t b_WAITPKG = 0x00000020;
constexpr uint32_t b_AVX512VBMI2 = 0x00000040;
constexpr uint32_t b_SHSTK = 0x00000080;
constexpr uint32_t b_GFNI = 0x00000100;
constexpr uint32_t b_VAES = 0x00000200;
constexpr uint32_t b_VPCLMULQDQ = 0x00000400;
constexpr uint32_t b_AVX512VNNI = 0x00000800;
constexpr uint32_t b_AVX512BITALG = 0x00001000;
constexpr uint32_t b_TMEM = 0x00002000;
constexpr uint32_t b_AVX512VPOPCNTDQ = 0x00004000;
constexpr uint32_t b_IA57 = 0x00010000;
constexpr uint32_t b_RDPID = 0x00400000;
constexpr uint32_t b_KL = 0x00800000;
constexpr uint32_t b_BLD = 0x01000000;
constexpr uint32_t b_CLDEMOTE = 0x02000000;
constexpr uint32_t b_MOVDIRI = 0x08000000;
constexpr uint32_t b_MOVDIR64B = 0x10000000;
constexpr uint32_t b_ENQCMD = 0x20000000;
constexpr uint32_t b_SGXLC = 0x40000000;
constexpr uint32_t b_PKS = 0x80000000;

// Features in edx for leaf 7 sub-leaf 0
constexpr uint32_t b_SGXKEYS = 0x00000002;
constexpr uint32_t b_AVX5124VNNIW = 0x00000004;
constexpr uint32_t b_AVX5124FMAPS = 0x00000008;
constexpr uint32_t b_FSRM = 0x00000010;
constexpr uint32_t b_UINTR = 0x00000020;
constexpr uint32_t b_AVX512VP2INTERSECT = 0x00000100;
constexpr uint32_t b_SRBDSCTRL = 0x00000200;
constexpr uint32_t b_MDCLEAR = 0x00000400;
constexpr uint32_t b_RTMAA = 0x00000800;
constexpr uint32_t b_RTMFA = 0x00002000;
constexpr uint32_t b_SERIALIZE = 0x00004000;
constexpr uint32_t b_HYBRID = 0x00008000;
constexpr uint32_t b_TSXLDTRK = 0x00010000;
constexpr uint32_t b_PCONFIG = 0x00040000;
constexpr uint32_t b_LBR = 0x00080000;
constexpr uint32_t b_IBT = 0x00100000;
constexpr uint32_t b_AMXBF16 = 0x00400000;
constexpr uint32_t b_AVX512FP16 = 0x00800000;
constexpr uint32_t b_AMXTILE = 0x01000000;
constexpr uint32_t b_AMXINT8 = 0x02000000;
constexpr uint32_t b_IBRRS = 0x04000000;
constexpr uint32_t b_STIBP = 0x08000000;
constexpr uint32_t b_L1D_FLUSH = 0x10000000;
constexpr uint32_t b_IA32_ARCH_CAPABILITIES = 0x20000000;
constexpr uint32_t b_IA32_CORE_CAPABILITIES = 0x40000000;
constexpr uint32_t b_SSBD = 0x80000000;

// Features in eax for leaf 7 sub-leaf 1
constexpr uint32_t b_SHA512 = 0x00000001;
constexpr uint32_t b_SM3 = 0x00000002;
constexpr uint32_t b_SM4 = 0x00000004;
constexpr uint32_t b_RAOINT = 0x00000008;
constexpr uint32_t b_AVXVNNI = 0x00000010;
constexpr uint32_t b_AVX512BF16 = 0x00000020;
constexpr uint32_t b_CMPCCXADD = 0x00000080;
constexpr uint32_t b_FRED = 0x00020000;
constexpr uint32_t b_LKGS = 0x00040000;
constexpr uint32_t b_WRMSRNS = 0x00080000;
constexpr uint32_t b_NMISRC = 0x00100000;
constexpr uint32_t b_AMXFP16 = 0x00200000;
constexpr uint32_t b_HRESET = 0x00400000;
constexpr uint32_t b_AVXIFMA = 0x00800000;
constexpr uint32_t b_MSRLIST = 0x08000000;
constexpr uint32_t b_MOVRS = 0x80000000;

// Features in ebx for leaf 7 sub-leaf 1
constexpr uint32_t b_PBNDKB = 0x00000002;

// Features in edx for leaf 7 sub-leaf 1
constexpr uint32_t b_AVXVNNIINT8 = 0x00000010;
constexpr uint32_t b_AVXNECONVERT = 0x00000020;
constexpr uint32_t b_AMXCOMPLEX = 0x00000100;
constexpr uint32_t b_AVXVNNIINT16 = 0x00000400;
constexpr uint32_t b_PREFETCHI = 0x00004000;
constexpr uint32_t b_USERMSR = 0x00008000;
constexpr uint32_t b_AVX10 = 0x00080000;
constexpr uint32_t b_APXF = 0x00200000;

// Features in eax for leaf 13 sub-leaf 1
constexpr uint32_t b_XSAVEOPT = 0x00000001;
constexpr uint32_t b_XSAVEC = 0x00000002;
constexpr uint32_t b_XSAVES = 0x00000008;
constexpr uint32_t b_XSAVEXFD = 0x00000010;

// Features in ebx for leaf 0x14 sub-leaf 0
constexpr uint32_t b_PTWRITE = 0x00000010;

// Keylocker leaf (%eax == 0x19)
constexpr uint32_t b_AESKLE = 0x00000001;
constexpr uint32_t b_WIDEKL = 0x00000004;

// Features in %eax for AMX sub-leaf (%eax == 0x1e, %ecx == 1)
constexpr uint32_t b_AMXFP8 = 0x00000010;
constexpr uint32_t b_AMX_TRANSPOSE = 0x00000020;
constexpr uint32_t b_AMX_TF32 = 0x00000040;
constexpr uint32_t b_AMX_AVX512 = 0x00000080;
constexpr uint32_t b_AMX_MOVRS = 0x00000100;

// Features in ebx for leaf 0x24
constexpr uint32_t b_AVX10_256 = 0x00020000;
constexpr uint32_t b_AVX10_512 = 0x00040000;

// Features in ecx for leaf 0x80000001
constexpr uint32_t b_LAHF_LM = 0x00000001;
constexpr uint32_t b_ABM = 0x00000020;
constexpr uint32_t b_SSE4a = 0x00000040;
constexpr uint32_t b_PRFCHW = 0x00000100;
constexpr uint32_t b_XOP = 0x00000800;
constexpr uint32_t b_LWP = 0x00008000;
constexpr uint32_t b_FMA4 = 0x00010000;
constexpr uint32_t b_TBM = 0x00200000;
constexpr uint32_t b_MWAITX = 0x20000000;

// Features in edx for leaf 0x80000001
constexpr uint32_t b_MMXEXT = 0x00400000;
constexpr uint32_t b_LM = 0x20000000;
constexpr uint32_t b_3DNOWP = 0x40000000;
constexpr uint32_t b_3DNOW = 0x80000000;

// Features in ebx for leaf 0x80000008
constexpr uint32_t b_CLZERO = 0x00000001;
constexpr uint32_t b_RDPRU = 0x00000010;
constexpr uint32_t b_WBNOINVD = 0x00000200;

#else

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
#endif

typedef struct cpu_basic_info cpu_basic_info;
typedef struct cpu_features cpu_features;

extern int check_cpuid();

void cpuid(uint32_t leaf, uint32_t registers[4]);

void cpuid_extended(uint32_t leaf, uint32_t sub_leaf, uint32_t registers[4]);

int get_cpu_features(cpu_features* features, cpu_basic_info* basic_info);

#ifdef CPUIDX_LANG_CPP
}
#endif

#endif //CPUIDX_H
