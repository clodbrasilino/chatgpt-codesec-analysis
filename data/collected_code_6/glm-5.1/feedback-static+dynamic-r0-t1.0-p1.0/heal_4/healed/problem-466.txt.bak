#include <stdio.h>
#include <stdlib.h>

int find_peak_element(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    if (size == 1) {
        return 0;
    }

    if (arr[0] >= arr[1]) {
        return 0;
    }

    if (arr[size - 1] >= arr[size - 2]) {
        return size - 1;
    }

    int low = 1;
    int high = size - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] >= arr[mid - 1] && arr[mid] >= arr[mid + 1]) {
            return mid;
        } else if (arr[mid] < arr[mid + 1]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main(int argc, char * const * const argv) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    int size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int peak_index = find_peak_element(arr, size);
    if (peak_index != -1) {
        printf("%d\n", peak_index);
    }

    free(arr);

    return EXIT_SUCCESS;
}