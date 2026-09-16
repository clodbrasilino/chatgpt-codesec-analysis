#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

static int lists_equal(const IntList *a, const IntList *b)
{
    size_t i;

    if (a->length != b->length) {
        return 0;
    }
    if (a->length == 0) {
        return 1;
    }
    if (a->data == NULL || b->data == NULL) {
        return 0;
    }
    for (i = 0; i < a->length; i++) {
        if (a->data[i] != b->data[i]) {
            return 0;
        }
    }
    return 1;
}

static size_t count_unique_lists(const IntList *lists, size_t list_count)
{
    size_t unique_count = 0;
    size_t i;
    size_t j;
    int is_unique;

    if (lists == NULL || list_count == 0) {
        return 0;
    }

    for (i = 0; i < list_count; i++) {
        is_unique = 1;
        for (j = 0; j < i; j++) {
            if (lists_equal(&lists[i], &lists[j])) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            unique_count++;
        }
    }

    return unique_count;
}

int main(void)
{
    const size_t list_count = 5;
    const int values[5][3] = {
        {1, 2, 3},
        {4, 5, 0},
        {1, 2, 3},
        {6, 0, 0},
        {4, 5, 0}
    };
    const size_t lengths[5] = {3, 2, 3, 1, 2};
    IntList *lists = NULL;
    size_t i;
    size_t result;

    lists = malloc(list_count * sizeof(*lists));
    if (lists == NULL) {
        fprintf(stderr, "Failed to allocate memory for lists\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_count; i++) {
        lists[i].data = malloc(lengths[i] * sizeof(*lists[i].data));
        if (lists[i].data == NULL) {
            fprintf(stderr, "Failed to allocate memory for list %zu\n", i);
            while (i > 0) {
                i--;
                free(lists[i].data);
                lists[i].data = NULL;
            }
            free(lists);
            lists = NULL;
            return EXIT_FAILURE;
        }
        memcpy(lists[i].data, values[i], lengths[i] * sizeof(*lists[i].data));
        lists[i].length = lengths[i];
    }

    result = count_unique_lists(lists, list_count);
    printf("Number of unique lists: %zu\n", result);

    for (i = 0; i < list_count; i++) {
        free(lists[i].data);
        lists[i].data = NULL;
    }
    free(lists);
    lists = NULL;

    return EXIT_SUCCESS;
}