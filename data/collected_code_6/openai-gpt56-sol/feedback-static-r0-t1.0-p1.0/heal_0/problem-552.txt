#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_linear(const long long sequence[], size_t length)
{
    if (sequence == NULL || length < 2U) {
        return true;
    }

    const long long difference = sequence[1] - sequence[0];

    for (size_t i = 2U; i < length; ++i) {
        if (sequence[i] - sequence[i - 1U] != difference) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(long long)) {
        return EXIT_FAILURE;
    }

    long long *sequence = NULL;

    if (length > 0U) {
        sequence = malloc(length * sizeof(*sequence));
        if (sequence == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0U; i < length; ++i) {
            if (scanf("%lld", &sequence[i]) != 1) {
                free(sequence);
                return EXIT_FAILURE;
            }
        }
    }

    const bool result = is_linear(sequence, length);
    free(sequence);

    if (printf("%s\n", result ? "Linear" : "Not linear") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}