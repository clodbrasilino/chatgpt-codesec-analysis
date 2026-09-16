#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_polite_number(uint64_t n, uint64_t *result)
{
    uint64_t value = 3;
    uint64_t count = 0;

    if (n == 0 || result == NULL) {
        return 0;
    }

    for (;;) {
        if ((value & (value - 1)) != 0) {
            ++count;
            if (count == n) {
                *result = value;
                return 1;
            }
        }

        if (value == UINT64_MAX) {
            return 0;
        }

        ++value;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
        fprintf(stderr, "Invalid n\n");
        return EXIT_FAILURE;
    }

    if (!nth_polite_number((uint64_t)input, &result)) {
        fprintf(stderr, "Unable to compute the requested polite number\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}