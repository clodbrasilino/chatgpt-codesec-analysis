#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

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
    
    return (bits_outside_range == 0) ? 1 : 0;
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
    
    /* Possible weaknesses found:
     *  Calling function 'check_bits_in_range' returns -1
     *  Assignment 'invalid_result_1=check_bits_in_range(0x00000000,8,3)', assigned value is -1
     */
    int invalid_result_1 = check_bits_in_range(0x00000000, 8, 3);
    /* Possible weaknesses found:
     *  Condition 'invalid_result_1==-1' is always true
     *  Condition 'invalid_result_1==-1' is always true [knownConditionTrueFalse]
     */
    if (invalid_result_1 == -1) {
        printf("Range [8, 3]: Invalid\n");
    } else {
        printf("Range [8, 3]: Valid\n");
    }
    
    /* Possible weaknesses found:
     *  Calling function 'check_bits_in_range' returns -1
     *  Assignment 'invalid_result_2=check_bits_in_range(0x00000000,0,32)', assigned value is -1
     */
    int invalid_result_2 = check_bits_in_range(0x00000000, 0, 32);
    /* Possible weaknesses found:
     *  Condition 'invalid_result_2==-1' is always true [knownConditionTrueFalse]
     *  Condition 'invalid_result_2==-1' is always true
     */
    if (invalid_result_2 == -1) {
        printf("Range [0, 32]: Invalid\n");
    } else {
        printf("Range [0, 32]: Valid\n");
    }
    
    int valid_result = check_bits_in_range(0xFFFFFFFF, 0, 31);
    printf("Range [0, 31]: %s\n", valid_result == 1 ? "Valid" : "Invalid");
    
    int edge_result_1 = check_bits_in_range(0x80000000, 31, 31);
    printf("Range [31, 31] with value 0x80000000: %s\n", 
           edge_result_1 == 1 ? "All bits in range" : 
           edge_result_1 == 0 ? "Bits outside range" : "Invalid range");
    
    int edge_result_2 = check_bits_in_range(0x7FFFFFFF, 31, 31);
    printf("Range [31, 31] with value 0x7FFFFFFF: %s\n", 
           edge_result_2 == 1 ? "All bits in range" : 
           edge_result_2 == 0 ? "Bits outside range" : "Invalid range");
    
    int full_range_result = check_bits_in_range(0x12345678, 0, 31);
    printf("Range [0, 31] with value 0x12345678: %s\n", 
           full_range_result == 1 ? "All bits in range" : 
           full_range_result == 0 ? "Bits outside range" : "Invalid range");
    
    return 0;
}