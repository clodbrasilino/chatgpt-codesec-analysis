#include <stddef.h>
#include <stdio.h>

size_t find_min_indices(const int arr[], size_t len, size_t out_indices[]) {
    size_t i;
    size_t count = 0;
    int min;

    if (arr == NULL || len == 0 || out_indices == NULL) {
        return 0;
    }

    min = arr[0];
    for (i = 1; i < len; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    for (i = 0; i < len; i++) {
        if (arr[i] == min) {
            out_indices[count] = i;
            count++;
        }
    }

    return count;
}

int main(void) {
    int arr[] = {3, 1, 4, 1, 5};
    size_t indices[5];
    size_t count;
    size_t i;

    count = find_min_indices(arr, 5, indices);

    printf("%zu\n", count);
    for (i = 0; i < count; i++) {
        printf("%zu ", indices[i]);
    }
    printf("\n");

    return 0;
}