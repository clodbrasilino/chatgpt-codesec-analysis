#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int find_min_indices(const int list[], size_t size, size_t **indices_out, size_t *count_out)
{
    size_t i;
    size_t count = 0;
    size_t *indices = NULL;
    int min;

    if (list == NULL || size == 0 || indices_out == NULL || count_out == NULL) {
        if (indices_out != NULL) {
            *indices_out = NULL;
        }
        if (count_out != NULL) {
            *count_out = 0;
        }
        return -1;
    }

    min = list[0];
    for (i = 1; i < size; i++) {
        if (list[i] < min) {
            min = list[i];
        }
    }

    for (i = 0; i < size; i++) {
        if (list[i] == min) {
            count++;
        }
    }

    if (count > (size_t)-1 / sizeof(size_t)) {
        *indices_out = NULL;
        *count_out = 0;
        return -1;
    }

    indices = malloc(count * sizeof(size_t));
    if (indices == NULL) {
        *indices_out = NULL;
        *count_out = 0;
        return -1;
    }

    count = 0;
    for (i = 0; i < size; i++) {
        if (list[i] == min) {
            indices[count] = i;
            count++;
        }
    }

    *indices_out = indices;
    *count_out = count;
    return 0;
}

int main(void)
{
    int list[] = {3, 1, 4, 1, 5, 9, 1};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t *indices = NULL;
    size_t count = 0;
    size_t i;
    int result;

    result = find_min_indices(list, size, &indices, &count);
    if (result != 0) {
        fprintf(stderr, "Error finding minimum indices\n");
        return 1;
    }

    for (i = 0; i < count; i++) {
        printf("%zu\n", indices[i]);
    }

    free(indices);
    return 0;
}