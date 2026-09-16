#include <stdio.h>
#include <stdlib.h>

int find_max_indices(const int *arr, size_t len, size_t **indices, size_t *count)
{
    size_t i;
    size_t n;
    int max;
    size_t *result;

    if (arr == NULL || indices == NULL || count == NULL || len == 0) {
        return -1;
    }

    max = arr[0];
    for (i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    n = 0;
    for (i = 0; i < len; i++) {
        if (arr[i] == max) {
            n++;
        }
    }

    result = malloc(n * sizeof(size_t));
    if (result == NULL) {
        return -1;
    }

    n = 0;
    for (i = 0; i < len; i++) {
        if (arr[i] == max) {
            result[n] = i;
            n++;
        }
    }

    *indices = result;
    *count = n;
    return 0;
}

int main(void)
{
    int data[] = {3, 7, 1, 7, 5, 7, 2};
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t *indices = NULL;
    size_t count = 0;
    size_t i;

    if (find_max_indices(data, len, &indices, &count) != 0) {
        fprintf(stderr, "Failed to find maximum indices\n");
        return EXIT_FAILURE;
    }

    printf("Indices of maximum value:");
    for (i = 0; i < count; i++) {
        printf(" %zu", indices[i]);
    }
    printf("\n");

    free(indices);
    return EXIT_SUCCESS;
}