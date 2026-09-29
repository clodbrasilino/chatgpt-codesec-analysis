#include <stdio.h>
#include <stdbool.h>

bool is_even(int number) {
    return (number % 2) == 0;
}

int main(void) {
    int test_numbers[] = {0, 1, 2, -3, -4, 100, 101};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (is_even(test_numbers[i])) {
            printf("%d is even\n", test_numbers[i]);
        } else {
            printf("%d is odd\n", test_numbers[i]);
        }
    }

    return 0;
}