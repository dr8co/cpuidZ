#if !(__x86_64__ || __86_64 || __amd64__ || __amd64 || __i386__ || __i386 || _M_AMD64 || _M_X64 || _M_IX86 || __X86__ || _X86_)
#error "The target arch is not x86."
#endif

#include <cpuidx.h>
#include <stdio.h>

#ifndef CPUIDX_BOOL_AVAILABLE
#include <stdbool.h>
#endif

/**
 * Prints basic CPU information.
 *
 * @param info A pointer to a \p cpu_basic_info structure containing the basic CPU information.
 */
void print_basic_info(const cpu_basic_info* const info) {
    puts("Basic CPU Information:");
    if (info->vendor[0] != '\0') printf("\tVendor: %s\n", info->vendor);
    if (info->brand[0] != '\0') printf("\tBrand : %s\n", info->brand);
    if (info->family) printf("\tFamily: 0x%x (%u)\n", info->family, info->family);
    if (info->model) printf("\tModel : 0x%x (%u)\n", info->model, info->model);
    if (info->stepping) printf("\tStepping id: 0x%x (%u)\n", info->stepping, info->stepping);

    if (info->highest_basic_leaf)
        printf("\tHighest basic function number implemented: 0x%x (%u)\n", info->highest_basic_leaf,
               info->highest_basic_leaf);
    if (info->highest_extended_leaf)
        printf("\tHighest extended function number implemented: 0x%x (%u)\n", info->highest_extended_leaf,
               info->highest_extended_leaf);
}

/**
 * Prints available CPU features.
 *
 * @param feats A pointer to a \p cpu_features structure containing the CPU features.
 */
void print_available_features(const cpu_features* feats) {
    static const char* const feature_names[] = {
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
        "TSC: Time Stamp Counter and RDTSC instruction", "MSR: Model-specific registers and RDMSR/WRMSR instructions",
        "PAE: Physical Address Extension", "MCE: Machine Check Exception",
        "CX8: CMPXCHG8B (compare-and-swap) instruction", "APIC: Onboard Advanced Programmable Interrupt Controller",
        "SEP: SYSENTER and SYSEXIT fast system call instructions", "MTRR: Memory Type Range Registers",
        "PGE: Page Global Enable bit in CR4", "MCA: Machine check architecture",
        "CMOV:Conditional move: CMOV, FCMOV and FCOMI instructions", "PAT: Page Attribute Table",
        "PSE36: 36-bit page size extension", "PSN: Processor Serial Number supported and enabled",
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
        "AVXIFMA: AVX Integer Fused Multiply-Add instructions",
        "MSRLIST: RDMSRLIST and WRMSRLIST instructions, and the IA32_BARRIER (02Fh) MSR",
        "MOVRS: MOVRS and PREFETCHRST2 instructions supported (memory read/prefetch with read-shared hint)",
        "PBNDKB: Total Storage Encryption: PBNDKB instruction and TSE_CAPABILITY (9F1h) MSR.",
        "AVXVNNIINT8: AVX Vector Neural Network Instructions with INT8 data",
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

    puts("Available CPU Features:");
    for (size_t i = 0; i < sizeof(feature_names) / sizeof(feature_names[0]); ++i) {
        if (feature_values[i]) {
            printf("- %s\n", feature_names[i]);
        }
    }
}

int main() {
    cpu_features features = {};
    cpu_basic_info basic_info = {};

    switch (get_cpu_features(&features, &basic_info)) {
        case -1:
            fputs("CPUID instruction is not supported by your cpu.\n", stderr);
            return 1;
        case 0:
            print_basic_info(&basic_info);
            putchar('\n');
            print_available_features(&features);
            return 0;
        default:
            fputs("Failed to get CPU features.\n", stderr);
            return 1;
    }
}
