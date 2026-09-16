#include <stdio.h>
#include <stdlib.h>

size_t *find_min_indices(const int arr[], size_t len, size_t *count)
{
    size_t i;
    size_t min_count;
    size_t pos;
    size_t *indices;
    int min;

    if (count == NULL) {
        return NULL;
    }

    if (arr == NULL || len == 0) {
        *count = 0;
        return NULL;
    }

    min = arr[0];
    min_count = 1;

    for (i = 1; i < len; i++) {
        if (arr[i] < min) {
            min = arr[i];
            min_count = 1;
        } else if (arr[i] == min) {
            min_count++;
        }
    }

    *count = min_count;

    if (min_count > (size_t)-1 / sizeof(*indices)) {
        return NULL;
    }

    indices = malloc(min_count * sizeof(*indices));
    if (indices == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 0; i < len; i++) {
        if (arr[i] == min) {
            indices[pos] = i;
            pos++;
        }
    }

    return indices;
}

int main(void)
{
    int values[] = {5, 2, 8, 2, 9, 2};
    size_t len = sizeof(values) / sizeof(values[0]);
    size_t count = 0;
    size_t i;
    size_t *indices;

    indices = find_min_indices(values, len, &count);

    if (indices == NULL) {
        if (count > 0) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        printf("No indices found.\n");
        return 1;
    }

    printf("Minimum value indices:");
    for (i = 0; i < count; i++) {
        printf(" %zu", indices[i]);
    }
    printf("\n");

    free(indices);
    return 0;
}