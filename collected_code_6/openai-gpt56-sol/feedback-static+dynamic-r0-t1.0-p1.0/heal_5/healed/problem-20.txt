#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_woodall(uint64_t number)
{
    uint64_t power_of_two = 2;

    for (uint64_t n = 1; n <= 63; ++n) {
        if (n <= UINT64_MAX / power_of_two &&
            n * power_of_two - 1 == number) {
            return true;
        }

        if (power_of_two > UINT64_MAX / 2) {
            break;
        }

        power_of_two *= 2;
    }

    return false;
}

int main(void)
{
    char input[128];
    char *start;
    char *end;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    printf("%s\n", is_woodall((uint64_t)value) ? "True" : "False");
    return EXIT_SUCCESS;
}