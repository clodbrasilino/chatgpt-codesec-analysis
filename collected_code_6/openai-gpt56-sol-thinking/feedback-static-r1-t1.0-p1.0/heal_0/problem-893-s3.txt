#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int get_last_elements(const int *const *sublists,
                      const size_t *lengths,
                      size_t sublist_count,
                      int **result)
{
    int *last_elements;
    size_t i;

    if (result == NULL) {
        return -1;
    }

    *result = NULL;

    if (sublist_count == 0) {
        return 0;
    }

    if (sublists == NULL || lengths == NULL) {
        return -1;
    }

    for (i = 0; i < sublist_count; ++i) {
        if (sublists[i] == NULL || lengths[i] == 0) {
            return -1;
        }
    }

    if (sublist_count > SIZE_MAX / sizeof(*last_elements)) {
        return -1;
    }

    last_elements = malloc(sublist_count * sizeof(*last_elements));
    if (last_elements == NULL) {
        return -1;
    }

    for (i = 0; i < sublist_count; ++i) {
        last_elements[i] = sublists[i][lengths[i] - 1];
    }

    *result = last_elements;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5};
    const int third[] = {6, 7, 8, 9};
    const int *sublists[] = {first, second, third};
    const size_t lengths[] = {
        sizeof(first) / sizeof(first[0]),
        sizeof(second) / sizeof(second[0]),
        sizeof(third) / sizeof(third[0])
    };
    const size_t sublist_count = sizeof(sublists) / sizeof(sublists[0]);
    int *last_elements = NULL;
    size_t i;

    if (get_last_elements(sublists, lengths, sublist_count,
                          &last_elements) != 0) {
        if (fprintf(stderr, "Failed to get last elements.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < sublist_count; ++i) {
        if (printf("%d%s", last_elements[i],
                   i + 1 == sublist_count ? "\n" : " ") < 0) {
            free(last_elements);
            return EXIT_FAILURE;
        }
    }

    free(last_elements);
    return EXIT_SUCCESS;
}