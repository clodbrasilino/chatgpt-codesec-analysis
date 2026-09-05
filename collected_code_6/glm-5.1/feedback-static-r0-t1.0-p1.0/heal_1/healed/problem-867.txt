#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_add_to_even(const int *arr, size_t size) {
    if (size == 0) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }

    if (sum % 2 == 0) {
        return 0;
    }

    return 1;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    size_t size = (size_t)(argc - 1);
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        if (val > INT_MAX || val < INT_MIN) {
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }

    int result = min_add_to_even(arr, size);

    printf("%d\n", result);

    free(arr);

    return 0;
}