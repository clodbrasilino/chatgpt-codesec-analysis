#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_demlo_number(uint64_t number)
{
    uint64_t square = number * number;
    uint64_t divisor = 1;

    while (divisor <= number / 10U) {
        divisor *= 10U;
    }

    while (divisor != 0U) {
        if (square % 10U != (number / divisor) % 10U) {
            return 0;
        }

        square /= 10U;
        divisor /= 10U;
    }

    return 1;
}

int main(void)
{
    char input[64];
    char *end;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value > UINT64_C(3037000499)) {
        return EXIT_FAILURE;
    }

    puts(is_demlo_number((uint64_t)value)
             ? "Demlo number"
             : "Not a Demlo number");

    return EXIT_SUCCESS;
}