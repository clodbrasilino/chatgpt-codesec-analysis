#include <stdio.h>
#include <stdlib.h>

int remove_duplicates(int *arr, size_t size, size_t *new_size);

int remove_duplicates(int *arr, size_t size, size_t *new_size) {
    if (arr == NULL || new_size == NULL) {
        return -1;
    }

    if (size == 0) {
        *new_size = 0;
        return 0;
    }

    size_t write_idx = 0;

    for (size_t i = 0; i < size; i++) {
        int is_duplicate = 0;
        for (size_t j = 0; j < write_idx; j++) {
            if (arr[i] == arr[j]) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            arr[write_idx] = arr[i];
            write_idx++;
        }
    }

    *new_size = write_idx;
    return 0;
}

int main(void) {
    int arr[] = {10, 20, 30, 20, 40, 50, 30, 60};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t new_size = 0;

    if (remove_duplicates(arr, size, &new_size) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < new_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}