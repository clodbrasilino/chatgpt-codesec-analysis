#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int compare_asc(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

int compare_desc(const void *a, const void *b) {
    return (*(const char *)b - *(const char *)a);
}

long next_bigger_number(long n) {
    if (n < 0) {
        return -1;
    }

    char digits[32];
    int len = snprintf(digits, sizeof(digits), "%ld", n);
    
    if (len <= 0 || len >= (int)sizeof(digits)) {
        return -1;
    }

    int i = len - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) {
        i--;
    }

    if (i < 0) {
        return -1;
    }

    int j = len - 1;
    while (digits[j] <= digits[i]) {
        j--;
    }

    char temp = digits[i];
    digits[i] = digits[j];
    digits[j] = temp;

    qsort(digits + i + 1, len - i - 1, sizeof(char), compare_asc);

    long result = strtol(digits, NULL, 10);
    
    if (result == LONG_MAX || result == LONG_MIN) {
        return -1;
    }

    return result;
}

int main(void) {
    long test_cases[] = {12, 513, 2017, 9, 111, 531, 123456789};
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        long result = next_bigger_number(test_cases[i]);
        if (result == -1) {
            printf("Input: %ld -> No bigger number possible\n", test_cases[i]);
        } else {
            printf("Input: %ld -> Next bigger: %ld\n", test_cases[i], result);
        }
    }

    return 0;
}