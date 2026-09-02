#include <stdio.h>
#include <stdbool.h>

bool can_represent_as_sum_of_powers_of_two(int n) {
    if (n < 0) {
        return false;
    }
    if (n == 0) {
        return true;
    }
    while (n > 0) {
        if (n & 1) {
            n >>= 1;
        } else {
            n >>= 1;
        }
        if (n == 0) {
            return true;
        }
        if (n & 1) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int test_numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 16, 17, 31, 32, 33, 63, 64, 65, 100, 127, 128, 129, 255, 256, 257, 511, 512, 513, 1023, 1024, 1025};
    int num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

    for (int i = 0; i < num_tests; i++) {
        int n = test_numbers[i];
        bool result = can_represent_as_sum_of_powers_of_two(n);
        printf("%d -> %s\n", n, result ? "true" : "false");
    }

    return 0;
}