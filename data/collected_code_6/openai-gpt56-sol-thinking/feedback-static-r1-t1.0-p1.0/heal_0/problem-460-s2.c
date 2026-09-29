#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} IntList;

static int get_first_elements(const IntList *lists, size_t list_count, int **result)
{
    int *first_elements;
    size_t i;

    if (result == NULL) {
        return -1;
    }

    *result = NULL;

    if (list_count == 0) {
        return 0;
    }

    if (lists == NULL || list_count > SIZE_MAX / sizeof(*first_elements)) {
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        if (lists[i].elements == NULL || lists[i].length == 0) {
            return -1;
        }
    }

    first_elements = malloc(list_count * sizeof(*first_elements));
    if (first_elements == NULL) {
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        first_elements[i] = lists[i].elements[0];
    }

    *result = first_elements;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5};
    const int third[] = {6, 7, 8, 9};
    const IntList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    const size_t list_count = sizeof(lists) / sizeof(lists[0]);
    int *first_elements = NULL;
    size_t i;

    if (get_first_elements(lists, list_count, &first_elements) != 0) {
        fputs("Failed to get first elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_count; ++i) {
        printf("%d%s", first_elements[i], i + 1 == list_count ? "\n" : " ");
    }

    free(first_elements);
    return EXIT_SUCCESS;
}