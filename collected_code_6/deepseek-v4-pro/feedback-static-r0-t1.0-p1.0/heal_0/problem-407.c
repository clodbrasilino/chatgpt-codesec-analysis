#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_chars(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

long long next_bigger_number(long long n) {
    char digits[32];
    int len;
    int i;
    int j;
    int pivot;
    char temp;
    long long result;
    char *endptr;

    if (n < 0) {
        return -1;
    }

    snprintf(digits, sizeof(digits), "%lld", n);
    len = (int)strlen(digits);

    pivot = -1;
    for (i = len - 2; i >= 0; i--) {
        if (digits[i] < digits[i + 1]) {
            pivot = i;
            break;
        }
    }

    if (pivot == -1) {
        return -1;
    }

    j = len - 1;
    while (j > pivot && digits[j] <= digits[pivot]) {
        j--;
    }

    temp = digits[pivot];
    digits[pivot] = digits[j];
    digits[j] = temp;

    qsort(digits + pivot + 1, len - pivot - 1, sizeof(char), compare_chars);

    result = strtoll(digits, &endptr, 10);
    if (*endptr != '\0') {
        return -1;
    }

    if (result <= n || result <= 0) {
        return -1;
    }

    return result;
}

int main(void) {
    long long test_values[] = {12, 513, 2017, 9, 111, 531, 123456789, 9876543210LL};
    size_t count = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        long long result = next_bigger_number(test_values[i]);
        printf("%lld -> %lld\n", test_values[i], result);
    }

    return 0;
}