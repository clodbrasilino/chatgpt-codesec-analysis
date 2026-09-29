#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Sublist;

size_t count_sublists_containing(const Sublist *sublists, size_t count, int target)
{
    size_t matches = 0;

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < sublists[i].length; ++j) {
            if (sublists[i].elements[j] == target) {
                ++matches;
                break;
            }
        }
    }

    return matches;
}

void free_sublists(Sublist *sublists, size_t count)
{
    if (sublists == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(sublists[i].elements);
    }

    free(sublists);
}

int main(void)
{
    int target;
    size_t count;
    Sublist *sublists = NULL;

    if (scanf("%d %zu", &target, &count) != 2) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*sublists)) {
        return EXIT_FAILURE;
    }

    if (count > 0) {
        sublists = calloc(count, sizeof(*sublists));
        if (sublists == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%zu", &sublists[i].length) != 1) {
            free_sublists(sublists, count);
            return EXIT_FAILURE;
        }

        if (sublists[i].length > SIZE_MAX / sizeof(*sublists[i].elements)) {
            free_sublists(sublists, count);
            return EXIT_FAILURE;
        }

        if (sublists[i].length > 0) {
            sublists[i].elements =
                malloc(sublists[i].length * sizeof(*sublists[i].elements));

            if (sublists[i].elements == NULL) {
                free_sublists(sublists, count);
                return EXIT_FAILURE;
            }
        }

        for (size_t j = 0; j < sublists[i].length; ++j) {
            if (scanf("%d", &sublists[i].elements[j]) != 1) {
                free_sublists(sublists, count);
                return EXIT_FAILURE;
            }
        }
    }

    size_t result = count_sublists_containing(sublists, count, target);

    if (printf("%zu\n", result) < 0) {
        free_sublists(sublists, count);
        return EXIT_FAILURE;
    }

    free_sublists(sublists, count);
    return EXIT_SUCCESS;
}