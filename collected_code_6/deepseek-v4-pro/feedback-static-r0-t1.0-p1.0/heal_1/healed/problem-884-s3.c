#include <stdio.h>
#include <stdint.h>

int check_bits_in_range(uint32_t value, uint32_t start, uint32_t end) {
    if (start > end || end > 31) {
        return -1;
    }
    
    uint32_t mask;
    
    if (end == 31) {
        if (start == 0) {
            mask = 0xFFFFFFFF;
        } else {
            mask = 0xFFFFFFFF << start;
        }
    } else {
        uint32_t bits_up_to_end = (1U << (end + 1)) - 1;
        if (start == 0) {
            mask = bits_up_to_end;
        } else {
            uint32_t bits_before_start = (1U << start) - 1;
            mask = bits_up_to_end ^ bits_before_start;
        }
    }
    
    uint32_t bits_outside_range = value & ~mask;
    
    if (bits_outside_range == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    uint32_t test_values[] = {0x00000000, 0x00000001, 0x00000002, 0x00000003,
                              0x00000004, 0x00000008, 0x00000010, 0x00000020,
                              0x00000040, 0x00000080, 0x00000100, 0x00000200,
                              0x00000400, 0x00000800, 0x00001000, 0x00002000,
                              0x00004000, 0x00008000, 0x00010000, 0x00020000};
    
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    printf("Testing range [0, 3]:\n");
    for (int i = 0; i < num_tests; i++) {
        int result = check_bits_in_range(test_values[i], 0, 3);
        printf("Value 0x%08X: %s\n", test_values[i], 
               result == 1 ? "All bits in range" : 
               result == 0 ? "Bits outside range" : "Invalid range");
    }
    
    printf("\nTesting range [4, 7]:\n");
    for (int i = 0; i < num_tests; i++) {
        int result = check_bits_in_range(test_values[i], 4, 7);
        printf("Value 0x%08X: %s\n", test_values[i], 
               result == 1 ? "All bits in range" : 
               result == 0 ? "Bits outside range" : "Invalid range");
    }
    
    printf("\nTesting range [8, 15]:\n");
    for (int i = 0; i < num_tests; i++) {
        int result = check_bits_in_range(test_values[i], 8, 15);
        printf("Value 0x%08X: %s\n", test_values[i], 
               result == 1 ? "All bits in range" : 
               result == 0 ? "Bits outside range" : "Invalid range");
    }
    
    printf("\nTesting invalid ranges:\n");
    printf("Range [8, 3]: %s\n", 
           check_bits_in_range(0x00000000, 8, 3) == -1 ? "Invalid" : "Valid");
    printf("Range [0, 32]: %s\n", 
           check_bits_in_range(0x00000000, 0, 32) == -1 ? "Invalid" : "Valid");
    printf("Range [0, 31]: %s\n", 
           check_bits_in_range(0xFFFFFFFF, 0, 31) == 1 ? "Valid" : "Invalid");
    
    return 0;
}