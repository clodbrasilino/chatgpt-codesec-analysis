#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t length;
} Sublist;

size_t find_min_length_sublist(const Sublist *sublists, size_t count, int *status)
{
    size_t i;
    size_t min_index;

    if (status == NULL) {
        return 0;
    }
    if (sublists == NULL || count == 0) {
        *status = -1;
        return 0;
    }

    min_index = 0;
    for (i = 1; i < count; i++) {
        if (sublists[i].length < sublists[min_index].length) {
            min_index = i;
        }
    }

    *status = 0;
    return min_index;
}

int main(void)
{
    Sublist *sublists;
    const size_t lengths[] = {5, 3, 7, 2};
    const size_t count = sizeof(lengths) / sizeof(lengths[0]);
    size_t i;
    size_t j;
    size_t min_index;
    int status = 0;

    sublists = malloc(count * sizeof(*sublists));
    if (sublists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        sublists[i].data = NULL;
        sublists[i].length = 0;
    }

    for (i = 0; i < count; i++) {
        sublists[i].data = malloc(lengths[i] * sizeof(*sublists[i].data));
        if (sublists[i].data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < i; j++) {
                free(sublists[j].data);
            }
            free(sublists);
            return EXIT_FAILURE;
        }
        sublists[i].length = lengths[i];
        for (j = 0; j < lengths[i]; j++) {
            sublists[i].data[j] = (int)(i * 10 + j);
        }
    }

    min_index = find_min_length_sublist(sublists, count, &status);
    if (status == 0) {
        printf("Sublist with minimum length: index %zu, length %zu\n",
               min_index, sublists[min_index].length);
        printf("Elements: ");
        for (j = 0; j < sublists[min_index].length; j++) {
            printf("%d ", sublists[min_index].data[j]);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Failed to find minimum length sublist\n");
    }

    for (i = 0; i < count; i++) {
        free(sublists[i].data);
    }
    free(sublists);

    return EXIT_SUCCESS;
}