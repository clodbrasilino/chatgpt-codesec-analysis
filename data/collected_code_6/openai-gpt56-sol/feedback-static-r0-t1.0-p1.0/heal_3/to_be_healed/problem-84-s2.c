#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int newman_conway(size_t n, uint64_t *result)
{
    uint64_t *sequence;
    size_t i;

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

    for (i = 2; i < n; ++i) {
        uint64_t previous = sequence[i - 1];
        size_t first_index;
        size_t second_index;

        if (previous == 0 || previous > i) {
            free(sequence);
            return -1;
        }

        first_index = (size_t)previous - 1;
        second_index = i - (size_t)previous;

        if (UINT64_MAX - sequence[first_index] < sequence[second_index]) {
            free(sequence);
            return -1;
        }

        sequence[i] = sequence[first_index] + sequence[second_index];
    }

    *result = sequence[n - 1];
    free(sequence);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        input == 0 || input > SIZE_MAX) {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    if (newman_conway((size_t)input, &result) != 0) {
        fprintf(stderr, "Unable to compute the requested term\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}