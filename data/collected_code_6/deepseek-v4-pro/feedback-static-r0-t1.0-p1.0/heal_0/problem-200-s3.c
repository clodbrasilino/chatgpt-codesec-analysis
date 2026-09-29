#include <stdio.h>
#include <stdlib.h>

int *find_max_indices(const int *arr, size_t len, size_t *out_count) {
    if (arr == NULL || len == 0 || out_count == NULL) {
        return NULL;
    }

    int max_val = arr[0];
    size_t count = 1;

    for (size_t i = 1; i < len; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            count = 1;
        } else if (arr[i] == max_val) {
            count++;
        }
    }

    int *indices = malloc(count * sizeof(*indices));
    if (indices == NULL) {
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < len; i++) {
        if (arr[i] == max_val) {
            indices[idx++] = (int)i;
        }
    }

    *out_count = count;
    return indices;
}

int main(void) {
    int data[] = {5, 2, 9, 1, 9, 7, 9};
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t count = 0;

    int *indices = find_max_indices(data, len, &count);

    if (indices == NULL) {
        fprintf(stderr, "Allocation failed or invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Maximum value indices: ");
    for (size_t i = 0; i < count; i++) {
        printf("%d", indices[i]);
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf("\n");

    free(indices);
    return EXIT_SUCCESS;
}