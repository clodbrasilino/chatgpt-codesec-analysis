#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int sumOddLengthSubarrays(const int *arr, int arrSize) {
    int total = 0;
    for (int i = 0; i < arrSize; i++) {
        for (int j = i; j < arrSize; j += 2) {
            for (int k = i; k <= j; k++) {
                total += arr[k];
            }
        }
    }
    return total;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    if (argv[1] == NULL) {
        return 1;
    }
    int arrSize = argc - 1;
    int *arr = (int *)malloc(arrSize * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < arrSize; i++) {
        if (argv[i + 1] == NULL) {
            free(arr);
            return 1;
        }
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' || val < 0 || val > INT_MAX) {
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }
    int result = sumOddLengthSubarrays(arr, arrSize);
    printf("%d\n", result);
    free(arr);
    return 0;
}