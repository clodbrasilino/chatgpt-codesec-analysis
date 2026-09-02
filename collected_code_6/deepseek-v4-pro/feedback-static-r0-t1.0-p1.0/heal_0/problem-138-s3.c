#include <stdio.h>
#include <stdbool.h>

bool can_be_represented_as_sum_of_powers_of_two(int number) {
    if (number <= 0) {
        return false;
    }
    return true;
}

int main(void) {
    int test_cases[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 16, 17, 31, 32, 33, -1, 0};
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        int num = test_cases[i];
        bool result = can_be_represented_as_sum_of_powers_of_two(num);
        printf("%d: %s\n", num, result ? "Yes" : "No");
    }

    return 0;
}