#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_difference(int *array, size_t size) {
    if (array == NULL || size < 2) {
        return -1;
    }

    int min_val = array[0];
    int max_val = array[0];

    for (size_t i = 1; i < size; i++) {
        if (array[i] < min_val) {
            min_val = array[i];
        } else if (array[i] > max_val) {
            max_val = array[i];
        }
    }

    return max_val - min_val;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
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

    int result = max_difference(arr, size);
    printf("%d\n", result);

    free(arr);
    return 0;
}