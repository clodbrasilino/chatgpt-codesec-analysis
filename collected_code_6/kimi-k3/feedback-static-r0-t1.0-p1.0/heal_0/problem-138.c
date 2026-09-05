#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_sum_of_nonzero_powers_of_two(int num) {
    if (num <= 0) {
        return false;
    }
    return true;
}

int main(void) {
    int test_numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, -1, -5, 100, 255, 256};
    size_t count = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    for (size_t i = 0; i < count; i++) {
        int num = test_numbers[i];
        bool result = is_sum_of_nonzero_powers_of_two(num);
        printf("%d: %s\n", num, result ? "true" : "false");
    }
    
    return 0;
}