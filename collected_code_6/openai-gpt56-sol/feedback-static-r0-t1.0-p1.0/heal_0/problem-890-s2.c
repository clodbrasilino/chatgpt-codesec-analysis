#include <stdio.h>
#include <stdlib.h>

static int find_extra_index(const int *longer, size_t longer_len,
                            const int *shorter, size_t shorter_len,
                            size_t *index)
{
    if (longer == NULL || shorter == NULL || index == NULL ||
        longer_len != shorter_len + 1U) {
        return 0;
    }

    size_t left = 0U;
    size_t right = shorter_len;

    while (left < right) {
        size_t middle = left + (right - left) / 2U;

        if (longer[middle] == shorter[middle]) {
            left = middle + 1U;
        } else {
            right = middle;
        }
    }

    *index = left;
    return 1;
}

int main(void)
{
    size_t shorter_len;

    if (scanf("%zu", &shorter_len) != 1 || shorter_len == SIZE_MAX) {
        return EXIT_FAILURE;
    }

    size_t longer_len = shorter_len + 1U;

    if (longer_len > SIZE_MAX / sizeof(int) ||
        (shorter_len != 0U && shorter_len > SIZE_MAX / sizeof(int))) {
        return EXIT_FAILURE;
    }

    int *longer = malloc(longer_len * sizeof(*longer));
    int *shorter = shorter_len == 0U
                       ? NULL
                       : malloc(shorter_len * sizeof(*shorter));

    if (longer == NULL || (shorter_len != 0U && shorter == NULL)) {
        free(longer);
        free(shorter);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < longer_len; ++i) {
        if (scanf("%d", &longer[i]) != 1) {
            free(longer);
            free(shorter);
            return EXIT_FAILURE;
        }

        if (i > 0U && longer[i] < longer[i - 1U]) {
            free(longer);
            free(shorter);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < shorter_len; ++i) {
        if (scanf("%d", &shorter[i]) != 1) {
            free(longer);
            free(shorter);
            return EXIT_FAILURE;
        }

        if (i > 0U && shorter[i] < shorter[i - 1U]) {
            free(longer);
            free(shorter);
            return EXIT_FAILURE;
        }
    }

    size_t index;
    int found = find_extra_index(longer, longer_len, shorter, shorter_len,
                                 &index);

    if (!found) {
        free(longer);
        free(shorter);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U, j = 0U; i < longer_len; ++i) {
        if (i == index) {
            continue;
        }

        if (j >= shorter_len || longer[i] != shorter[j]) {
            free(longer);
            free(shorter);
            return EXIT_FAILURE;
        }

        ++j;
    }

    printf("%zu\n", index);

    free(longer);
    free(shorter);
    return EXIT_SUCCESS;
}