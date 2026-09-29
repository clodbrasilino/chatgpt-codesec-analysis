#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int repeat_tuple(const Tuple tuple, size_t n, Tuple **result)
{
    Tuple *repeated;
    size_t i;

    if (result == NULL) {
        return EINVAL;
    }

    *result = NULL;

    if (n == 0) {
        return 0;
    }

    if (n > SIZE_MAX / sizeof(*repeated)) {
        return EOVERFLOW;
    }

    repeated = malloc(n * sizeof(*repeated));
    if (repeated == NULL) {
        return ENOMEM;
    }

    for (i = 0; i < n; ++i) {
        repeated[i] = tuple;
    }

    *result = repeated;
    return 0;
}

int main(void)
{
    const Tuple tuple = {1, 2};
    const size_t repetitions = 5;
    Tuple *result = NULL;
    int status;
    size_t i;

    status = repeat_tuple(tuple, repetitions, &result);
    if (status != 0) {
        fprintf(stderr, "repeat_tuple failed: %d\n", status);
        return EXIT_FAILURE;
    }

    for (i = 0; i < repetitions; ++i) {
        if (printf("(%d, %d)%s",
                   result[i].first,
                   result[i].second,
                   i + 1 < repetitions ? " " : "\n") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}