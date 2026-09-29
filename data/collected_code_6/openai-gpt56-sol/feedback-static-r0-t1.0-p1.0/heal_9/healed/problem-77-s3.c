#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int64_t digit_sum_difference(uint64_t number)
{
    int64_t difference = 0;

    do {
        uint64_t digit = number % UINT64_C(10);
        difference += (digit % UINT64_C(2) == 0)
                          ? (int64_t)digit
                          : -(int64_t)digit;
        number /= UINT64_C(10);
    } while (number != 0);

    return difference;
}

int main(void)
{
    char input[256];
    char *end;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(ferror(stdin) ? "Failed to read input.\n" : "Invalid number.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[strlen(input) - 1] != '\n' && !feof(stdin)) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || value > UINT64_MAX) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", digit_sum_difference((uint64_t)value));
    return EXIT_SUCCESS;
}