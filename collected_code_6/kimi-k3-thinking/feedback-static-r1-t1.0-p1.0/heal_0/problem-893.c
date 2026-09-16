#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

static int *get_last_elements(const IntList *lists, size_t list_count, size_t *out_count)
{
    int *result;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (lists == NULL || list_count == 0) {
        return NULL;
    }

    if (list_count > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    result = malloc(list_count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < list_count; i++) {
        if (lists[i].data == NULL || lists[i].length == 0) {
            free(result);
            return NULL;
        }
        result[i] = lists[i].data[lists[i].length - 1];
    }

    *out_count = list_count;
    return result;
}

int main(void)
{
    int first[] = {1, 2, 3};
    int second[] = {4, 5};
    int third[] = {6, 7, 8, 9};
    IntList lists[3];
    int *last_elements;
    size_t count = 0;
    size_t i;

    lists[0].data = first;
    lists[0].length = sizeof(first) / sizeof(first[0]);
    lists[1].data = second;
    lists[1].length = sizeof(second) / sizeof(second[0]);
    lists[2].data = third;
    lists[2].length = sizeof(third) / sizeof(third[0]);

    last_elements = get_last_elements(lists, sizeof(lists) / sizeof(lists[0]), &count);
    if (last_elements == NULL) {
        fprintf(stderr, "Error: unable to retrieve last elements\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("%d\n", last_elements[i]);
    }

    free(last_elements);
    last_elements = NULL;

    return EXIT_SUCCESS;
}