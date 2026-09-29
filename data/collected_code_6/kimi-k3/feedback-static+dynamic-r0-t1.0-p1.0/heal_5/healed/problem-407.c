#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int compare_asc(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

long next_bigger_number(long n) {
    if (n < 0) {
        return -1;
    }

    size_t buf_size = (size_t)snprintf(NULL, 0, "%ld", n) + 1;
    char *digits = malloc(buf_size);
    if (digits == NULL) {
        return -1;
    }

    int len = snprintf(digits, buf_size, "%ld", n);
    if (len <= 0 || (size_t)len >= buf_size) {
        free(digits);
        return -1;
    }

    int i = len - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) {
        i--;
    }

    if (i < 0) {
        free(digits);
        return -1;
    }

    int j = len - 1;
    while (j > i && digits[j] <= digits[i]) {
        j--;
    }

    if (j <= i) {
        free(digits);
        return -1;
    }

    char temp = digits[i];
    digits[i] = digits[j];
    digits[j] = temp;

    if (len - i - 1 > 1) {
        qsort(digits + i + 1, (size_t)(len - i - 1), sizeof(char), compare_asc);
    }

    errno = 0;
    char *endptr;
    long result = strtol(digits, &endptr, 10);
    
    free(digits);

    if (errno == ERANGE || endptr == digits || *endptr != '\0') {
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