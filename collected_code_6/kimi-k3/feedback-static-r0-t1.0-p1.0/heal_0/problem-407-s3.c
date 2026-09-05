#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define MAX_DIGITS 20

static int compare_digits(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

static int compare_digits_desc(const void *a, const void *b) {
    return (*(const char *)b - *(const char *)a);
}

long long next_bigger_number(long long n) {
    if (n < 0) {
        return -1;
    }

    char digits[MAX_DIGITS];
    int len = snprintf(digits, MAX_DIGITS, "%lld", n);
    
    if (len <= 0 || len >= MAX_DIGITS) {
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

    qsort(digits + i + 1, len - i - 1, sizeof(char), compare_digits);

    errno = 0;
    char *endptr = NULL;
    long long result = strtoll(digits, &endptr, 10);
    
    if (errno == ERANGE || endptr == digits || *endptr != '\0') {
        return -1;
    }

    return result;
}

int main(void) {
    long long test_cases[] = {12, 513, 2017, 9, 111, 531, 123456789};
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        long long result = next_bigger_number(test_cases[i]);
        if (result == -1) {
            printf("Input: %lld -> No bigger number possible\n", test_cases[i]);
        } else {
            printf("Input: %lld -> Next bigger: %lld\n", test_cases[i], result);
        }
    }

    return EXIT_SUCCESS;
}