#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_single_element(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    if (size == 1) {
        return arr[0];
    }
    size_t low = 0;
    size_t high = size - 1;
    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (mid % 2 == 1) {
            mid--;
        }
        if (arr[mid] == arr[mid + 1]) {
            low = mid + 2;
        } else {
            high = mid;
        }
    }
    return arr[low];
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    size_t size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (size_t i = 0; i < size; ++i) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (errno == ERANGE || val > INT_MAX || val < INT_MIN || *endptr != '\0') {
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }
    int result = find_single_element(arr, size);
    printf("%d\n", result);
    free(arr);
    return 0;
}