#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} Sublist;

bool find_minimum_length_sublist(
    const Sublist *sublists,
    size_t count,
    const Sublist **result
) {
    size_t minimum_index = 0;

    if (sublists == NULL || result == NULL || count == 0) {
        return false;
    }

    *result = NULL;

    for (size_t i = 0; i < count; ++i) {
        if (sublists[i].length > 0 && sublists[i].elements == NULL) {
            return false;
        }

        if (sublists[i].length < sublists[minimum_index].length) {
            minimum_index = i;
        }
    }

    *result = &sublists[minimum_index];
    return true;
}

int main(void) {
    static const int first[] = {1, 2, 3, 4};
    static const int second[] = {5, 6};
    static const int third[] = {7, 8, 9};

    const Sublist sublists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    const Sublist *minimum = NULL;
    const size_t count = sizeof(sublists) / sizeof(sublists[0]);

    if (!find_minimum_length_sublist(sublists, count, &minimum)) {
        return EXIT_FAILURE;
    }

    if (printf("Minimum length: %zu\nSublist:", minimum->length) < 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < minimum->length; ++i) {
        if (printf(" %d", minimum->elements[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}