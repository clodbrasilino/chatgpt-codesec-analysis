#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    LAST_ELEMENTS_OK = 0,
    LAST_ELEMENTS_INVALID_ARGUMENT,
    LAST_ELEMENTS_EMPTY_SUBLIST,
    LAST_ELEMENTS_ALLOCATION_FAILURE
} LastElementsStatus;

static LastElementsStatus get_last_elements(
    const int *const sublists[],
    const size_t lengths[],
    size_t count,
    int **result
) {
    int *last_elements;
    size_t i;

    if (result == NULL) {
        return LAST_ELEMENTS_INVALID_ARGUMENT;
    }

    *result = NULL;

    if (count == 0) {
        return LAST_ELEMENTS_OK;
    }

    if (sublists == NULL || lengths == NULL ||
        count > SIZE_MAX / sizeof(*last_elements)) {
        return LAST_ELEMENTS_INVALID_ARGUMENT;
    }

    for (i = 0; i < count; ++i) {
        if (sublists[i] == NULL) {
            return LAST_ELEMENTS_INVALID_ARGUMENT;
        }

        if (lengths[i] == 0) {
            return LAST_ELEMENTS_EMPTY_SUBLIST;
        }
    }

    last_elements = malloc(count * sizeof(*last_elements));
    if (last_elements == NULL) {
        return LAST_ELEMENTS_ALLOCATION_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        last_elements[i] = sublists[i][lengths[i] - 1];
    }

    *result = last_elements;
    return LAST_ELEMENTS_OK;
}

int main(void) {
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5};
    const int third[] = {6, 7, 8, 9};
    const int *const sublists[] = {first, second, third};
    const size_t lengths[] = {
        sizeof(first) / sizeof(first[0]),
        sizeof(second) / sizeof(second[0]),
        sizeof(third) / sizeof(third[0])
    };
    const size_t count = sizeof(sublists) / sizeof(sublists[0]);
    int *last_elements = NULL;
    LastElementsStatus status;
    size_t i;

    status = get_last_elements(sublists, lengths, count, &last_elements);
    if (status != LAST_ELEMENTS_OK) {
        if (fprintf(stderr, "Unable to get last elements: error %d\n", status) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (printf("%d%s", last_elements[i], i + 1 == count ? "\n" : " ") < 0) {
            free(last_elements);
            return EXIT_FAILURE;
        }
    }

    free(last_elements);
    return EXIT_SUCCESS;
}