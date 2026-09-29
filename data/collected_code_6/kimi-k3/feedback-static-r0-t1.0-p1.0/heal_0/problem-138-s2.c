#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_sum_of_nonzero_powers_of_2(unsigned int num) {
    return (num != 0U);
}

int main(void) {
    unsigned int test_numbers[] = {0U, 1U, 2U, 3U, 4U, 5U, 7U, 8U, 10U, 15U, 16U, 31U, 100U};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    printf("Checking if numbers can be represented as sum of non-zero powers of 2:\n");
    printf("(Note: Non-zero powers of 2 are 1, 2, 4, 8, 16, ...)\n\n");
    
    for (size_t i = 0U; i < num_tests; i++) {
        unsigned int num = test_numbers[i];
        bool result = is_sum_of_nonzero_powers_of_2(num);
        
        printf("%u: %s\n", num, result ? "Yes" : "No");
    }
    
    printf("\nExplanation:\n");
    printf("- 0: Cannot be represented (need at least one term)\n");
    printf("- Any positive integer: Can be represented using binary representation\n");
    printf("  Example: 5 = 4 + 1 = 2^2 + 2^0\n");
    printf("  Example: 10 = 8 + 2 = 2^3 + 2^1\n");
    
    return 0;
}