#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_demlo_number(uint64_t number)
{
    uint64_t square = number * number;
    uint64_t divisor = UINT64_C(1);

    while (divisor <= number / UINT64_C(10)) {
        divisor *= UINT64_C(10);
    }

    do {
        if (square % UINT64_C(10) !=
            (number / divisor) % UINT64_C(10)) {
            return 0;
        }

        square /= UINT64_C(10);
        divisor /= UINT64_C(10);
    } while (divisor != 0);

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
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