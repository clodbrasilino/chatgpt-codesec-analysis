#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_single(const int *arr, int size) {
    int low = 0;
    int high = size - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;
        int half = mid - low;

        if (half % 2 != 0) {
            if (arr[mid] == arr[mid - 1]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        } else {
            if (arr[mid] == arr[mid + 1]) {
                low = mid + 2;
            } else {
                high = mid;
            }
        }
    }

    return arr[low];
}

long safe_strtol(const char *str, int *success) {
    char *endptr;
    long val = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        *success = 0;
    }
    return val;
}

int main(int argc, char const * const argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    int size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));

    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        int success = 1;
        long val = safe_strtol(argv[i + 1], &success);
        if (!success) {
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    if (size % 2 == 0) {
        free(arr);
        return EXIT_FAILURE;
    }

    int result = find_single(arr, size);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}