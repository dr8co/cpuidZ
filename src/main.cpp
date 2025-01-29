#if !(__x86_64__ || __86_64 || __amd64__ || __amd64 || __i386__ || __i386 || _M_AMD64 || _M_X64 || _M_IX86 || __X86__ || _X86_)
#error "The target arch is not x86."
#endif

#include <cpuidx.h>
#include <unordered_map>
#include <string>
#include <print>
#include <tuple>
#include <limits>
#include <cassert>

/// Concept to check if std::hash<T> is defined.
/// 
/// This concept ensures that a type T can be hashed using std::hash.
/// 
/// \tparam T The type to check for hashability.
template <class T>
concept Hashable = requires(T t) {
    { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
};

/// Hash combination utility function.
/// 
/// Combines the hash values of multiple arguments into a single hash value.
/// 
/// \tparam T The type of the first argument.
/// \tparam Other The types of the other arguments.
/// \param first The first argument to hash.
/// \param other The other arguments to hash.
/// \return The combined hash value of all arguments.
template <class T, class... Other>
    requires Hashable<T> && (Hashable<Other> && ...)
constexpr std::size_t hash_combine(const T& first, const Other&... other) {
    static constexpr std::size_t golden_ratio = std::numeric_limits<std::size_t>::digits == 64
                                                    ? 0x9e3779b97f4a7c13 // 64-bit golden ratio
                                                    : 0x9e3779b9; // 32-bit golden ratio
    // Start with the hash value of the first argument
    std::size_t seed = std::hash<T>{}(first);

    // Combine the hash values of all arguments
    ((seed ^= (std::hash<Other>{}(other) + golden_ratio + (seed << 6) + (seed >> 2))), ...);
    return seed;
}

/// Custom hasher for std::tuple.
/// 
/// Provides a way to hash a std::tuple by combining the hash values of its elements.
struct tuple_hash {
    /// Hashes a std::tuple by combining the hash values of its elements.
    ///
    /// \tparam Types The types of the elements in the tuple.
    /// \param t The tuple to hash.
    /// \return The combined hash value of the tuple elements.
    template <class... Types>
    std::size_t operator()(const std::tuple<Types...>& t) const {
        return std::apply([]<class... T>(T&&... args) {
            return hash_combine(std::forward<T>(args)...);
        }, t);
    }
};

/// Custom hasher for std::pair.
/// 
/// Provides a way to hash a std::pair by combining the hash values of its elements.
struct pair_hash {
    /// Hashes a std::pair by combining the hash values of its elements.
    /// 
    /// \tparam T1 The type of the first element in the pair.
    /// \tparam T2 The type of the second element in the pair.
    /// \param p The pair to hash.
    /// \return The combined hash value of the pair elements.
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        if constexpr (Hashable<T1> && Hashable<T2>)
            return hash_combine(p.first, p.second);
        else return tuple_hash{}(std::make_tuple(p.first, p.second));
    }
};

/// Prints basic CPU information.
/// \param info A reference to a \p cpu_basic_info structure containing the basic CPU information.
void print_basic_info(const cpu_basic_info& info) {
    std::println("Basic CPU Information:");
    if (info.vendor[0] != '\0') std::println("\tVendor     : {}", info.vendor);

    if (info.brand[0] != '\0') std::println("\tBrand      : {}", info.brand);

    if (const auto fam = info.family; fam)
        std::println("\tFamily     : {:<#4x} ({})", fam, fam);

    if (const auto mdl = info.model; mdl)
        std::println("\tModel      : {:<#4x} ({})", mdl, mdl);

    if (const auto step = info.stepping; step)
        std::println("\tStepping id: {:<#4x} ({})", step, step);

    if (const auto hl = info.highest_leaf; hl)
        std::println("\tHighest feature leaf: {:#x} ({})", hl, hl);

    if (const auto hxl = info.highest_extended_leaf; hxl)
        std::println("\tHighest extended feature leaf: {:#x} ({})", hxl, hxl);
}


/// Prints available CPU features.
/// \param feats A reference to a \p cpu_features structure containing the CPU features.
void print_available_features(const cpu_features& feats) {
    static const std::unordered_map<std::pair<std::string, std::string>, bool, pair_hash> featureMap = {
        {{"SSE3", "(Prescott New Instructions - PNI)"}, feats.SSE3},
        {{"PCLMULQDQ", "(carry-less multiply) instruction"}, feats.PCLMULQDQ},
        {{"DTES64", "64-bit debug store"}, feats.DTES64},
        {{"MONITOR", "MONITOR and MWAIT instructions (PNI)"}, feats.MONITOR},
        {{"DSCPL", "CPL qualified debug store"}, feats.DSCPL},
        {{"VMX", "Virtual Machine eXtensions"}, feats.VMX},
        {{"SMX", "Safer Mode Extensions (LaGrande) (GETSEC instruction)"}, feats.SMX},
        {{"EIST", "Enhanced SpeedStep"}, feats.EIST},
        {{"TM2", "Thermal Monitor 2"}, feats.TM2},
        {{"SSSE3", "Supplemental SSE3 instructions"}, feats.SSSE3},
        {{"CNXTID", "L1 Context ID"}, feats.CNXTID},
        {{"SDBG", "Silicon Debug Interface"}, feats.SDBG},
        {{"FMA", "Fused multiply-add (FMA3)"}, feats.FMA},
        {{"CMPXCHG16B", "CMPXCHG16B instruction"}, feats.CMPXCHG16B},
        {{"xTPR", "Can disable sending task priority messages"}, feats.xTPR},
        {{"PDCM", "Perfmon & debug capability"}, feats.PDCM},
        {{"PCID", "Process context identifiers"}, feats.PCID},
        {{"DCA", "Direct cache access for DMA writes"}, feats.DCA},
        {{"SSE41", "SSE4.1 instructions"}, feats.SSE41},
        {{"SSE42", "SSE4.2 instructions"}, feats.SSE42},
        {{"x2APIC", "enhanced APIC"}, feats.x2APIC},
        {{"MOVBE", "MOVBE instruction (big-endian)"}, feats.MOVBE},
        {{"POPCNT", "POPCNT instruction"}, feats.POPCNT},
        {{"TSCDeadline", "APIC implements one-shot operation using a TSC deadline value"}, feats.TSCDeadline},
        {{"AESNI", "AES instruction set"}, feats.AESNI},
        {{"XSAVE", "Extensible processor state save/restore:XSAVE, XRSTOR, XSETBV, XGETBV instructions"}, feats.XSAVE},
        {{"OSXSAVE", "XSAVE enabled by OS"}, feats.OSXSAVE},
        {{"AVX", "Advanced Vector Extensions (256-bit SIMD)"}, feats.AVX},
        {{"F16C", "Floating-point conversion instructions to/from FP16 format"}, feats.F16C},
        {{"RDRND", "on-chip random number generator"}, feats.RDRND},
        {{"HYPRVSR", "Hypervisor present"}, feats.HYPRVSR},
        {{"FPU", "Onboard x87 FPU"}, feats.FPU},
        {{"VME", "Virtual 8086 mode extensions (such as VIF, VIP, PVI)"}, feats.VME},
        {{"DE", "Debugging extensions (CR4 bit 3)"}, feats.DE},
        {{"PSE", "Page Size Extension (4 MB pages)"}, feats.PSE},
        {{"TSC", "Time Stamp Counter and RDTSC instruction"}, feats.TSC},
        {{"MSR", "Model-specific registers and RDMSR/WRMSR instructions"}, feats.MSR},
        {{"PAE", "Physical Address Extension"}, feats.PAE},
        {{"MCE", "Machine Check Exception"}, feats.MCE},
        {{"CX8", "CMPXCHG8B (compare-and-swap) instruction"}, feats.CX8},
        {{"APIC", "Onboard Advanced Programmable Interrupt Controller"}, feats.APIC},
        {{"SEP", "SYSENTER and SYSEXIT fast system call instructions"}, feats.SEP},
        {{"MTRR", "Memory Type Range Registers"}, feats.MTRR},
        {{"PGE", "Page Global Enable bit in CR4"}, feats.PGE},
        {{"MCA", "Machine check architecture"}, feats.MCA},
        {{"CMOV", "Conditional move: CMOV, FCMOV and FCOMI instructions"}, feats.CMOV},
        {{"PAT", "Page Attribute Table"}, feats.PAT},
        {{"PSE36", "36-bit page size extension"}, feats.PSE36},
        {{"PSN", "Processor Serial Number supported and enabled"}, feats.PSN},
        {{"CLFSH", "CLFLUSH cache line flush instruction (SSE2)"}, feats.CLFSH},
        {{"DS", "Debug store: save trace of executed jumps"}, feats.DS},
        {{"ACPI", "Onboard thermal control MSRs for ACPI"}, feats.ACPI},
        {{"MMX", "MMX instructions (64-bit SIMD)"}, feats.MMX},
        {{"FXSR", "FXSAVE, FXRSTOR instructions, CR4 bit 9"}, feats.FXSR},
        {{"SSE", "Streaming SIMD Extensions instructions (128-bit SIMD)"}, feats.SSE},
        {{"SSE2", "SSE2 instructions"}, feats.SSE2},
        {{"SS", "CPU cache implements self-snoop"}, feats.SS},
        {{"HTT", "Max APIC IDs reserved field is Valid"}, feats.HTT},
        {{"TM", "Thermal monitor automatically limits temperature"}, feats.TM},
        {{"IA64", "IA64 processor emulating x86"}, feats.IA64},
        {{"PBE", "Pending Break Enable (PBE# pin) wakeup capability"}, feats.PBE},
        {{"FSGSBASE", "Access to base of %fs and %gs"}, feats.FSGSBASE},
        {{"SGX", "Software Guard Extensions"}, feats.SGX},
        {{"BMI", "Bit Manipulation Instruction Set 1"}, feats.BMI},
        {{"HLE", "TSX Hardware Lock Elision"}, feats.HLE},
        {{"AVX2", "Advanced Vector Extensions 2"}, feats.AVX2},
        {{"FDPXO", "x87 FPU data pointer register updated on exceptions only"}, feats.FDPXO},
        {{"SMEP", "Supervisor Mode Execution Prevention"}, feats.SMEP},
        {{"BMI2", "Bit Manipulation Instruction Set 2"}, feats.BMI2},
        {{"ENH_MOVSB", "Enhanced REP MOVSB/STOSB"}, feats.ENH_MOVSB},
        {{"INVPCID", "INVPCID instruction"}, feats.INVPCID},
        {{"RTM", "TSX Restricted Transactional Memory"}, feats.RTM},
        {{"MPX", "Intel MPX (Memory Protection Extensions)"}, feats.MPX},
        {{"AVX512F", "AVX-512 Foundation"}, feats.AVX512F},
        {{"AVX512DQ", "AVX-512 Doubleword and Quadword Instructions"}, feats.AVX512DQ},
        {{"RDSEED", "RDSEED instruction"}, feats.RDSEED},
        {{"ADX", "Intel ADX (Multi-Precision Add-Carry Instruction Extensions)"}, feats.ADX},
        {{"SMAP", "Supervisor Mode Access Prevention"}, feats.SMAP},
        {{"AVX512IFMA", "AVX-512 Integer Fused Multiply-Add Instructions"}, feats.AVX512IFMA},
        {{"CLFLUSHOPT", "CLFLUSHOPT instruction"}, feats.CLFLUSHOPT},
        {{"CLWB", "Cache line writeback instruction"}, feats.CLWB},
        {{"PT", "Intel Processor Trace"}, feats.PT},
        {{"AVX512PF", "AVX-512 Prefetch Instructions"}, feats.AVX512PF},
        {{"AVX512ER", "AVX-512 Exponential and Reciprocal Instructions"}, feats.AVX512ER},
        {{"AVX512CD", "AVX-512 Conflict Detection Instructions"}, feats.AVX512CD},
        {{"SHA", "SHA-1 and SHA-256 extensions"}, feats.SHA},
        {{"AVX512BW", "AVX-512 Byte and Word Instructions"}, feats.AVX512BW},
        {{"AVX512VL", "AVX-512 Vector Length Extensions"}, feats.AVX512VL},
        {{"PREFTCHWT1", "PREFETCHWT1 instruction"}, feats.PREFTCHWT1},
        {{"AVX512VBMI", "AVX-512 Vector Bit Manipulation Instructions"}, feats.AVX512VBMI},
        {{"UMIP", "User-Mode Instruction Prevention"}, feats.UMIP},
        {{"PKU", "Memory Protection Keys for User-mode pages"}, feats.PKU},
        {{"OSPKE", "PKU enabled by OS"}, feats.OSPKE},
        {{"WAITPKG", "Timed pause and user-level monitor/wait instructions (TPAUSE, UMONITOR, UMWAIT)"}, feats.WAITPKG},
        {{"AVX512VBMI2", "AVX-512 Vector Bit Manipulation Instructions 2"}, feats.AVX512VBMI2},
        {{"SHSTK", "Control flow enforcement (CET):shadow stack"}, feats.SHSTK},
        {{"GFNI", "Galois Field instructions"}, feats.GFNI},
        {{"VAES", "Vector AES instruction set (VEX-256/EVEX)"}, feats.VAES},
        {{"VPCLMULQDQ", "CLMUL instruction set (VEX-256/EVEX)"}, feats.VPCLMULQDQ},
        {{"AVX512VNNI", "AVX-512 Vector Neural Network Instructions"}, feats.AVX512VNNI},
        {{"AVX512BITALG", "AVX-512 BITALG instructions"}, feats.AVX512BITALG},
        {{"TMEM", "Total Memory Encryption MSRs available"}, feats.TMEM},
        {{"AVX512VPOPCNTDQ", "AVX-512 Vector Population Count Double and Quad-word"}, feats.AVX512VPOPCNTDQ},
        {{"IA57", "5-level paging (57 address bits)"}, feats.IA57},
        {{"RDPID", "Read Processor ID instruction and IA32_TSC_AUX MSR"}, feats.RDPID},
        {{"KL", "AES Key Locker"}, feats.KL},
        {{"BLD", "Bus lock debug exceptions"}, feats.BLD},
        {{"CLDEMOTE", "Cache line demote instruction"}, feats.CLDEMOTE},
        {{"MOVDIRI", "MOVDIRI instruction"}, feats.MOVDIRI},
        {{"MOVDIR64B", "MOVDIR64B (64-byte direct store) instruction"}, feats.MOVDIR64B},
        {{"ENQCMD", "Enqueue Stores and EMQCMD/EMQCMDS instructions"}, feats.ENQCMD},
        {{"SGXLC", "SGX Launch Configuration"}, feats.SGXLC},
        {{"PKS", "Protection Keys for supervisor-mode pages"}, feats.PKS},
        {{"SGXKEYS", "Attestation Services for Intel SGX"}, feats.SGXKEYS},
        {{"AVX5124VNNIW", "AVX-512 4-register Neural Network Instructions"}, feats.AVX5124VNNIW},
        {{"AVX5124FMAPS", "AVX-512 4-register Multiply Accumulation Single precision"}, feats.AVX5124FMAPS},
        {{"FSRM", "Fast Short REP MOV"}, feats.FSRM},
        {{"UINTR", "User Inter-processor Interrupts"}, feats.UINTR},
        {
            {
                "AVX512VP2INTERSECT", "AVX-512 vector intersection instructions on 32/64-bit integers"
            },
            feats.AVX512VP2INTERSECT
        },
        {{"SRBDSCTRL", "Special Register Buffer Data Sampling Mitigations"}, feats.SRBDSCTRL},
        {{"MDCLEAR", "VERW instruction clears CPU buffers"}, feats.MDCLEAR},
        {{"RTMAA", "(rtm-always-abort): All TSX transactions are aborted"}, feats.RTMAA},
        {{"RTMFA", "(rtm-force-abort): TSX_FORCE_ABORT (MSR 0x10f) is available"}, feats.RTMFA},
        {{"SERIALIZE", "SERIALIZE instruction"}, feats.SERIALIZE},
        {{"HYBRID", "Hybrid processor (Mixture of CPU types in processor topology)"}, feats.HYBRID},
        {
            {"TSXLDTRK", "TSX load address tracking suspend/resume instructions (TSUSLDTRK and TRESLDTRK)"},
            feats.TSXLDTRK
        },
        {{"PCONFIG", "Platform configuration (Memory Encryption Technologies Instructions)"}, feats.PCONFIG},
        {{"LBR", "Architectural Last Branch Records"}, feats.LBR},
        {{"IBT", "Control flow enforcement (CET): indirect branch tracking"}, feats.IBT},
        {{"AMXBF16", "AMX tile computation on bfloat16 numbers"}, feats.AMXBF16},
        {{"AVX512FP16", "AVX-512 half-precision floating-point arithmetic instructions"}, feats.AVX512FP16},
        {{"AMXTILE", "AMX tile load/store instructions"}, feats.AMXTILE},
        {{"AMXINT8", "AMX tile computation on 8-bit integers"}, feats.AMXINT8},
        {
            {
                "IBRRS", "Indirect Branch Restricted Speculation (IBRS) and Indirect Branch Prediction Barrier (IBPB)"
            },
            feats.IBRRS
        },
        {{"STIBP", "Single Thread Indirect Branch Predictor"}, feats.STIBP},
        {{"L1D_FLUSH", "IA32_FLUSH_CMD MSR"}, feats.L1D_FLUSH},
        {
            {
                "IA32_ARCH_CAPABILITIES", "IA32_ARCH_CAPABILITIES MSR (lists speculative side channel mitigations)"
            },
            feats.IA32_ARCH_CAPABILITIES
        },
        {
            {
                "IA32_CORE_CAPABILITIES", "IA32_CORE_CAPABILITIES MSR (lists model-specific core capabilities)"
            },
            feats.IA32_CORE_CAPABILITIES
        },
        {{"SSBD", "Speculative Store Bypass Disable"}, feats.SSBD},
        {{"SHA512", "SHA-512 extensions"}, feats.SHA512},
        {{"SM3", "SM3 hash extensions"}, feats.SM3},
        {{"SM4", "SM4 cipher extensions"}, feats.SM4},
        {{"RAOINT", "Remote Atomic Operations on integers: AADD, AAND, AOR, AXOR instructions"}, feats.RAOINT},
        {{"AVXVNNI", "AVX Vector Neural Network Instructions (VNNI) (VEX encoded)"}, feats.AVXVNNI},
        {{"AVX512BF16", "AVX-512 instructions for bfloat16 numbers"}, feats.AVX512BF16},
        {{"CMPCCXADD", "CMPccXADD instructions"}, feats.CMPCCXADD},
        {{"FRED", "Flexible Return and Event Delivery"}, feats.FRED},
        {{"LKGS", "LKGS Instruction"}, feats.LKGS},
        {{"WRMSRNS", "WRMSRNS instruction (non-serializing write to MSRs)"}, feats.WRMSRNS},
        {{"NMISRC", "NMI source reporting"}, feats.NMISRC},
        {{"AMXFP16", "AMX instructions for FP16 numbers"}, feats.AMXFP16},
        {
            {
                "HRESET",
                "HRESET instruction, IA32_HRESET_ENABLE (17DAh) MSR, and Processor History Reset Leaf (EAX=20h)"
            },
            feats.HRESET
        },
        {{"AVXIFMA", "AVX Integer Fused Multiply-Add instructions"}, feats.AVXIFMA},
        {{"MSRLIST", "RDMSRLIST and WRMSRLIST instructions, and the IA32_BARRIER (02Fh) MSR"}, feats.MSRLIST},
        {
            {
                "MOVRS", "MOVRS and PREFETCHRST2 instructions supported (memory read/prefetch with read-shared hint)"
            },
            feats.MOVRS
        },
        {{"PBNDKB", "Total Storage Encryption: PBNDKB instruction and TSE_CAPABILITY (9F1h) MSR."}, feats.PBNDKB},
        {{"AVXVNNIINT8", "AVX Vector Neural Network Instructions with INT8 data"}, feats.AVXVNNIINT8},
        {
            {"AVXNECONVERT", "AVX no-exception FP conversion instructions (bfloat16↔FP32 and FP16→FP32)"},
            feats.AVXNECONVERT
        },
        {{"AMXCOMPLEX", "AMX support for \"complex\" tiles (TCMMIMFP16PS and TCMMRLFP16PS)"}, feats.AMXCOMPLEX},
        {{"AVXVNNIINT16", "AVX VNNI INT16 instructions"}, feats.AVXVNNIINT16},
        {{"PREFETCHI", "Instruction-cache prefetch instructions (PREFETCHIT0 and PREFETCHIT1)"}, feats.PREFETCHI},
        {{"USERMSR", "User-mode MSR access instructions (URDMSR and UWRMSR)"}, feats.USERMSR},
        {{"AVX10", "AVX10 Converged Vector ISA"}, feats.AVX10},
        {{"APXF", "Advanced Performance Extensions, Foundation"}, feats.APXF},
        {
            {"XSAVEOPT", "XSAVEOPT instruction: save state-components that have been modified since last XRSTOR"},
            feats.XSAVEOPT
        },
        {{"XSAVEC", "XSAVEC instruction: save/restore state with compaction"}, feats.XSAVEC},
        {{"XSAVES", "XSAVES and XRSTORS instructions and IA32_XSS MSR"}, feats.XSAVES},
        {{"XSAVEXFD", "XFD (Extended Feature Disable) supported"}, feats.XSAVEXFD},
        {{"PTWRITE", "PTWRITE instruction supported"}, feats.PTWRITE},
        {{"AESKLE", "AES \"Key Locker\" Instructions enabled"}, feats.AESKLE},
        {{"WIDEKL", "AES \"Wide Key Locker\" Instructions"}, feats.WIDEKL},
        {{"AMXFP8", "AMX float8 support"}, feats.AMXFP8},
        {{"AMX_TRANSPOSE", "AMX Transposition instruction support"}, feats.AMX_TRANSPOSE},
        {{"AMX_TF32", "AMX tf32/fp19 support"}, feats.AMX_TF32},
        {{"AMX_AVX512", "AMX-AVX512 support"}, feats.AMX_AVX512},
        {{"AMX_MOVRS", "AMX-MOVRS support"}, feats.AMX_MOVRS},
        {{"AVX10_256", "256-bit vector support is present"}, feats.AVX10_256},
        {{"AVX10_512", "512-bit vector support is present"}, feats.AVX10_512},
        {{"LAHF_LM", "LAHF/SAHF in long mode"}, feats.LAHF_LM},
        {{"ABM", "Advanced bit manipulation (LZCNT and POPCNT)"}, feats.ABM},
        {{"SSE4a", "SSE4a instructions"}, feats.SSE4a},
        {{"PRFCHW", "PREFETCH and PREFETCHW instructions"}, feats.PRFCHW},
        {{"XOP", "XOP instruction set"}, feats.XOP},
        {{"LWP", "Light Weight Profiling"}, feats.LWP},
        {{"FMA4", "4-operand fused multiply-add instructions"}, feats.FMA4},
        {{"TBM", "Trailing Bit Manipulation"}, feats.TBM},
        {{"MWAITX", "MONITORX and MWAITX instructions"}, feats.MWAITX},
        {{"MMXEXT", "Extended MMX"}, feats.MMXEXT},
        {{"LM", "Long mode"}, feats.LM},
        {{"3DNOWP", "Extended 3DNow!"}, feats.x3DNOWP},
        {{"3DNOW", "3DNow!"}, feats.x3DNOW},
        {{"CLZERO", "CLZERO instruction"}, feats.CLZERO},
        {{"RDPRU", "RDPRU instruction"}, feats.RDPRU},
        {{"WBNOINVD", "WBNOINVD instruction"}, feats.WBNOINVD},
    };

    // Print available features
    std::println("Available CPU Features:");
    for (const auto& [name, enabled] : featureMap) {
        if (enabled)
            std::println("- {:<13}: {}", name.first, name.second);
    }
}

int main([[maybe_unused]] const int argc, [[maybe_unused]] char** argv) {
    cpu_features features;
    cpu_basic_info basic_info;

    switch (get_cpu_features(&features, &basic_info)) {
        case -1:
            std::println(stderr, "CPUID instruction is not supported by your cpu.");
            return 1;
        case 0:
            print_basic_info(basic_info);
            std::println();
            print_available_features(features);
            return 0;
        default:
            std::println(stderr, "Failed to get CPU features");
            return 1;
    }
}
