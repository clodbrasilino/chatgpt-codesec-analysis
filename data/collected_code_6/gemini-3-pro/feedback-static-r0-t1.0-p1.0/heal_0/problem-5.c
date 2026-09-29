#include <stdio.h>
#include <limits.h>

int count_ways_to_tile(int n, unsigned long long *result) {
    unsigned long long prev2;
    unsigned long long prev1;
    unsigned long long current;
    unsigned long long term;
    int i;

    if (result == NULL) {
        return -1;
    }
    if (n < 0) {
        return -1;
    }
    if (n % 2 != 0) {
        *result = 0;
        return 0;
    }
    if (n == 0) {
        *result = 1;
        return 0;
    }
    if (n == 2) {
        *result = 3;
        return 0;
    }

    prev2 = 1;
    prev1 = 3;
    current = 0;

    for (i = 4; i <= n; i += 2) {
        if (prev1 > ULLONG_MAX / 4) {
            return -2;
        }
        term = 4 * prev1;
        if (term < prev2) {
            return -2;
        }
        current = term - prev2;
        prev2 = prev1;
        prev1 = current;
    }

    *result = current;
    return 0;
}

int main(void) {
    int test_n_values[] = { 0, 1, 2, 4, 12, 100 };
    size_t num_tests = sizeof(test_n_values) / sizeof(test_n_values[0]);
    unsigned long long ways = 0;
    int status;
    size_t j;

    for (j = 0; j < num_tests; j++) {
        status = count_ways_to_tile(test_n_values[j], &ways);
        if (status == 0) {
            printf("%d %llu\n", test_n_values[j], ways);
        } else if (status == -1) {
            printf("%d Error: Invalid input\n", test_n_values[j]);
        } else if (status == -2) {
            printf("%d Error: Integer overflow\n", test_n_values[j]);
        }
    }

    return 0;
}