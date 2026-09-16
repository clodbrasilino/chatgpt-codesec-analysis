#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int newman_conway(size_t n, size_t *result)
{
    size_t *sequence;

    if (result == NULL || n == 0 || n > SIZE_MAX / sizeof(*sequence)) {
        return -1;
    }

    sequence = malloc(n * sizeof(*sequence));
    if (sequence == NULL) {
        return -1;
    }

    sequence[0] = 1;

    if (n >= 2) {
        sequence[1] = 1;
    }

    for (size_t i = 2; i < n; ++i) {
        size_t one_based_index = i + 1;
        size_t previous = sequence[i - 1];
        size_t first_index = one_based_index - previous;
        size_t second_index = one_based_index - sequence[i - 2];

        if (first_index == 0 || second_index == 0 ||
            first_index > i || second_index > i ||
            sequence[first_index - 1] > SIZE_MAX - sequence[second_index - 1]) {
            free(sequence);
            return -1;
        }

        sequence[i] = sequence[first_index - 1] + sequence[second_index - 1];
    }

    *result = sequence[n - 1];
    free(sequence);
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long input;
    size_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input == 0 || input > SIZE_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (newman_conway((size_t)input, &result) != 0) {
        fprintf(stderr, "Unable to compute the sequence value\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", result);
    return EXIT_SUCCESS;
}