#include <stdio.h>
#include <stdbool.h>

bool is_non_prime(int num) {
    if (num < 2) {
        return true;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int test_cases[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        int num = test_cases[i];
        printf("%d: %s\n", num, is_non_prime(num) ? "non-prime" : "prime");
    }

    return 0;
}