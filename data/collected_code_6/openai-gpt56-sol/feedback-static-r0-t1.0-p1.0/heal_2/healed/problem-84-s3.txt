#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int newman_conway(size_t n, size_t *result)
{
    if (result == NULL || n == 0 || n > SIZE_MAX / sizeof(size_t)) {
        return -1;
    }

    size_t *sequence = malloc(n * sizeof(*sequence));
    if (sequence == NULL) {
        return -1;
    }

    sequence[0] = 1;

    if (n > 1) {
        sequence[1] = 1;
    }

    for (size_t i = 2; i < n; ++i) {
        size_t previous = sequence[i - 1];

        if (previous == 0 || previous > i) {
            free(sequence);
            return -1;
        }

        size_t first_index = previous - 1;
        size_t second_index = i - previous;

        if (sequence[first_index] >
            SIZE_MAX - sequence[second_index]) {
            free(sequence);
            return -1;
        }

        sequence[i] = sequence[first_index] + sequence[second_index];
    }

    *result = sequence[n - 1];
    free(sequence);
    return 0;
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long input = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input == 0 ||
        input > (unsigned long long)SIZE_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    size_t result;
    if (newman_conway((size_t)input, &result) != 0) {
        fprintf(stderr, "Unable to compute the sequence value\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", result);
    return EXIT_SUCCESS;
}