#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int64_t digit_sum_difference(uint64_t number)
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
    char input[22];
    char *end = NULL;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", digit_sum_difference((uint64_t)value));
    return EXIT_SUCCESS;
}