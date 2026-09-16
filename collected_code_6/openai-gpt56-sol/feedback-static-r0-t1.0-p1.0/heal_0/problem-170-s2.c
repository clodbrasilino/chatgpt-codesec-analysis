#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>

static bool sum_range(const int64_t *list, size_t length, size_t first,
                      size_t last, int64_t *result)
{
    if (list == NULL || result == NULL || first > last || last >= length) {
        return false;
    }

    int64_t sum = 0;

    for (size_t i = first; i <= last; ++i) {
        if ((list[i] > 0 && sum > INT64_MAX - list[i]) ||
            (list[i] < 0 && sum < INT64_MIN - list[i])) {
            return false;
        }
        sum += list[i];
    }

    *result = sum;
    return true;
}

int main(void)
{
    size_t length;
    size_t first;
    size_t last;
    int64_t result;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int64_t)) {
        fprintf(stderr, "Invalid list length.\n");
        return EXIT_FAILURE;
    }

    int64_t *list = malloc(length * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%" SCNd64, &list[i]) != 1) {
            fprintf(stderr, "Invalid list element.\n");
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%zu %zu", &first, &last) != 2) {
        fprintf(stderr, "Invalid range.\n");
        free(list);
        return EXIT_FAILURE;
    }

    if (!sum_range(list, length, first, last, &result)) {
        fprintf(stderr, "Invalid range or arithmetic overflow.\n");
        free(list);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fprintf(stderr, "Output error.\n");
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}