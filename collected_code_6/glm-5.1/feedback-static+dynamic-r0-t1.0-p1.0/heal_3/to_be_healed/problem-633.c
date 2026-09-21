#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long sum_of_xor_pairs(const int *arr, size_t n) {
    unsigned long long sum = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            sum += (unsigned long long)(arr[i] ^ arr[j]);
        }
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    size_t n = (size_t)(argc - 1);
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (size_t i = 0; i < n; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (endptr == argv[i + 1] || *endptr != '\0' || errno == ERANGE || val < INT_MIN || val > INT_MAX) {
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }
    unsigned long long result = sum_of_xor_pairs(arr, n);
    printf("%llu\n", result);
    free(arr);
    return 0;
}