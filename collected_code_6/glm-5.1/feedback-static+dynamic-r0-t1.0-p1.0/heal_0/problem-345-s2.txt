#include <stdio.h>
#include <stdlib.h>

int* find_differences(const int* arr, size_t size, size_t* out_size) {
    if (arr == NULL || out_size == NULL) {
        return NULL;
    }

    if (size < 2) {
        *out_size = 0;
        return NULL;
    }

    *out_size = size - 1;

    int* diff_arr = (int*)malloc(*out_size * sizeof(int));
    if (diff_arr == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *out_size; i++) {
        diff_arr[i] = arr[i + 1] - arr[i];
    }

    return diff_arr;
}

int main(void) {
    int list[] = {10, 15, 22, 8, 5};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t diff_size = 0;

    int* differences = find_differences(list, size, &diff_size);

    if (differences != NULL) {
        for (size_t i = 0; i < diff_size; i++) {
            printf("%d ", differences[i]);
        }
        printf("\n");
        free(differences);
    } else if (diff_size > 0) {
        printf("Allocation failed\n");
    } else {
        printf("Not enough elements to find differences\n");
    }

    return 0;
}