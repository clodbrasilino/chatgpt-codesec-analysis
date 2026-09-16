#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int count_sequences(size_t n, size_t m, uint64_t *result)
{
    uint64_t *previous = NULL;
    uint64_t *current = NULL;

    if (result == NULL) {
        return -1;
    }

    if (n == 0U) {
        *result = 1U;
        return 0;
    }

    if (m == 0U || m > SIZE_MAX / sizeof(*previous)) {
        *result = 0U;
        return m == 0U ? 0 : -1;
    }

    previous = calloc(m, sizeof(*previous));
    current = calloc(m, sizeof(*current));
    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return -1;
    }

    for (size_t value = 0U; value < m; ++value) {
        previous[value] = 1U;
    }

    for (size_t length = 2U; length <= n; ++length) {
        uint64_t prefix = 0U;

        for (size_t value = 0U; value < m; ++value) {
            size_t index = value / 2U;

            if (index > 0U) {
                if (UINT64_MAX - prefix < previous[index - 1U]) {
                    free(previous);
                    free(current);
                    return -1;
                }
                prefix += previous[index - 1U];
            }

            current[value] = prefix;
        }

        uint64_t *temporary = previous;
        previous = current;
        current = temporary;
    }

    *result = 0U;
    for (size_t value = 0U; value < m; ++value) {
        if (UINT64_MAX - *result < previous[value]) {
            free(previous);
            free(current);
            return -1;
        }
        *result += previous[value];
    }

    free(previous);
    free(current);
    return 0;
}

int main(void)
{
    size_t n;
    size_t m;
    uint64_t result;

    errno = 0;
    if (scanf("%zu %zu", &n, &m) != 2 || errno != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_sequences(n, m, &result) != 0) {
        fputs("Unable to compute result\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}