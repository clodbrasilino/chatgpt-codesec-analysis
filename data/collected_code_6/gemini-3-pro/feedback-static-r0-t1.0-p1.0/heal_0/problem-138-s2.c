#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_sum_of_powers_of_two(int n) {
    if (n <= 0) {
        return false;
    }
    if ((n & 1) != 0) {
        return false;
    }
    return true;
}

int main(void) {
    int test_cases[] = {0, 1, 2, 6, 10, 14, 15, -4};
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_cases; i++) {
        int n = test_cases[i];
        bool result = check_sum_of_powers_of_two(n);
        printf("%d: %s\n", n, result ? "True" : "False");
    }
    
    return EXIT_SUCCESS;
}