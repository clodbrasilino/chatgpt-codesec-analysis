#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_desc(const void *a, const void *b) {
    return *(const char *)b - *(const char *)a;
}

int cmp_asc(const void *a, const void *b) {
    return *(const char *)a - *(const char *)b;
}

long long next_bigger_number(long long n) {
    char digits[32];
    int len = snprintf(digits, sizeof(digits), "%lld", n);
    if (len <= 0 || len >= (int)sizeof(digits)) return -1;

    int i = len - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) i--;

    if (i < 0) return -1;

    int j = len - 1;
    while (digits[j] <= digits[i]) j--;

    char tmp = digits[i];
    digits[i] = digits[j];
    digits[j] = tmp;

    qsort(digits + i + 1, len - i - 1, sizeof(char), cmp_asc);

    char *endptr;
    long long result = strtoll(digits, &endptr, 10);
    if (endptr == digits || *endptr != '\0') return -1;

    return result;
}

int main(void) {
    long long test_cases[] = {
        123, 321, 2017, 987654321, 998877665544332211LL, 1, 10, 11, 123456789, 534976
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        long long input = test_cases[i];
        long long output = next_bigger_number(input);
        printf("%lld -> %lld\n", input, output);
    }

    return 0;
}