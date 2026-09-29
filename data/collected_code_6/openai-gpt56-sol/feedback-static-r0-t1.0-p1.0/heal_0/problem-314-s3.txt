#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int64_t max_non_adjacent_sum(const int64_t *top, const int64_t *bottom, size_t n)
{
    int64_t previous = 0;
    int64_t current = 0;

    for (size_t i = 0; i < n; ++i) {
        int64_t column_max = top[i] > bottom[i] ? top[i] : bottom[i];
        int64_t include = previous + column_max;
        int64_t exclude = current;
        int64_t next = include > exclude ? include : exclude;

        previous = current;
        current = next;
    }

    return current;
}

int main(void)
{
    size_t n;

    if (scanf("%zu", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *top = malloc(n * sizeof(*top));
    int64_t *bottom = malloc(n * sizeof(*bottom));

    if (n != 0 && (top == NULL || bottom == NULL)) {
        free(top);
        free(bottom);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        if (scanf("%" SCNd64, &top[i]) != 1) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (scanf("%" SCNd64, &bottom[i]) != 1) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    int64_t result = max_non_adjacent_sum(top, bottom, n);
    printf("%" PRId64 "\n", result);

    free(top);
    free(bottom);
    return EXIT_SUCCESS;
}