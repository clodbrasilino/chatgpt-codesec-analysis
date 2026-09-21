#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_difference_of_two_squares(int64_t number)
{
    uint64_t magnitude;

    if (number < 0) {
        magnitude = (uint64_t)(-(number + 1)) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)number;
    }

    return magnitude % UINT64_C(4) != UINT64_C(2);
}

int main(void)
{
    char input[128];
    char *end;
    intmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoimax(input, &end, 10);

    if (end == input || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_difference_of_two_squares((int64_t)value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}