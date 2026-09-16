#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int last_two_factorial_digits(uint64_t n)
{
    unsigned int result = 1U;

    for (uint64_t i = 2U; i <= n; ++i) {
        result = (result * (unsigned int)(i % 100U)) % 100U;
        if (result == 0U) {
            break;
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    unsigned int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid non-negative integer\n");
        return EXIT_FAILURE;
    }

    result = last_two_factorial_digits((uint64_t)input);
    printf("%02u\n", result);

    return EXIT_SUCCESS;
}