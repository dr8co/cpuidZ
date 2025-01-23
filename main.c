#include <stdio.h>
#include <stdint.h>

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

int main()
{
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
