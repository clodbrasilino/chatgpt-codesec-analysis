#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_demlo_number(uint64_t number)
{
    uint64_t square = number * number;

    do {
        if (square % UINT64_C(10) != number % UINT64_C(10)) {
            return 0;
        }

        square /= UINT64_C(10);
        number /= UINT64_C(10);
    } while (number != 0);

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t value;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno != 0 || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_C(3037000499)) {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_demlo_number((uint64_t)value)
             ? "Demlo number"
             : "Not a Demlo number");

    free(input);
    return EXIT_SUCCESS;
}