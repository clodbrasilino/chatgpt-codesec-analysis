#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int repeat_tuple(const Tuple tuple, size_t n, Tuple **result)
{
    Tuple *repeated;

    if (result == NULL) {
        return EINVAL;
    }

    *result = NULL;

    if (n == 0U) {
        return 0;
    }

    if (n > SIZE_MAX / sizeof(*repeated)) {
        return EOVERFLOW;
    }

    repeated = malloc(n * sizeof(*repeated));
    if (repeated == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0U; i < n; ++i) {
        repeated[i] = tuple;
    }

    *result = repeated;
    return 0;
}

int main(void)
{
    const Tuple tuple = {1, 2};
    const size_t n = 5U;
    Tuple *repeated = NULL;
    int status = repeat_tuple(tuple, n, &repeated);

    if (status != 0) {
        fprintf(stderr, "Failed to repeat tuple: error %d\n", status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < n; ++i) {
        if (printf("(%d, %d)%s",
                   repeated[i].first,
                   repeated[i].second,
                   i + 1U == n ? "\n" : " ") < 0) {
            free(repeated);
            return EXIT_FAILURE;
        }
    }

    free(repeated);
    return EXIT_SUCCESS;
}