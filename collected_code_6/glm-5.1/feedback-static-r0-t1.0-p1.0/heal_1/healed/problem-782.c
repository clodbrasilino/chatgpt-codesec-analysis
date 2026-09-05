#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        if (argv[i] == NULL || argv[i][0] == '\0') {
            return 1;
        }
        char *endptr;
        long val = strtol(argv[i], &endptr, 10);
        if (*endptr != '\0' || val < 0 || val > INT_MAX) {
            return 1;
        }
    }
    int arrSize = argc - 1;
    int *arr = (int *)malloc(arrSize * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < arrSize; i++) {
        arr[i] = (int)strtol(argv[i + 1], NULL, 10);
    }
    int result = sumOddLengthSubarrays(arr, arrSize);
    printf("%d\n", result);
    free(arr);
    return 0;
}