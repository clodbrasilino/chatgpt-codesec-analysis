#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define MAX_DIGITS 24
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int cmp_desc(const void *a, const void *b) {
    return *(const char *)b - *(const char *)a;
}

int cmp_asc(const void *a, const void *b) {
    return *(const char *)a - *(const char *)b;
}

long long next_bigger_number(long long n) {
    if (n < 0) return -1;

    int req_len = snprintf(NULL, 0, "%lld", n);
    if (req_len < 0) return -1;
    if (req_len >= MAX_DIGITS) return -1;

    char *digits = malloc(req_len + 2);
    if (!digits) return -1;

    int len = snprintf(digits, req_len + 1, "%lld", n);
    if (len < 0 || len != req_len) {
        free(digits);
        return -1;
    }

    if (len == 1) {
        free(digits);
        return -1;
    }

    int i = len - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) i--;

    if (i < 0) {
        free(digits);
        return -1;
    }

    int j = len - 1;
    while (digits[j] <= digits[i]) j--;

    char tmp = digits[i];
    digits[i] = digits[j];
    digits[j] = tmp;

    int suffix_len = len - i - 1;
    if (suffix_len > 1) {
        qsort(digits + i + 1, suffix_len, sizeof(char), cmp_asc);
    }

    digits[len] = '\0';

    char *endptr = NULL;
    errno = 0;
    long long result = strtoll(digits, &endptr, 10);
    if (endptr == digits || *endptr != '\0' || errno == ERANGE) {
        free(digits);
        return -1;
    }

    if (result <= n) {
        free(digits);
        return -1;
    }

    free(digits);
    return result;
}

int main(void) {
    long long test_cases[] = {
        123, 321, 2017, 987654321, 998877665544332211LL, 1, 10, 11, 123456789, 534976
    };
    size_t num_tests = ARRAY_SIZE(test_cases);

    for (size_t i = 0; i < num_tests; ++i) {
        long long input = test_cases[i];
        long long output = next_bigger_number(input);
        printf("%lld -> %lld\n", input, output);
    }

    return 0;
}