#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint64_t highest_power_of_two(uint64_t number)
{
    uint64_t result = UINT64_C(0);

    while (number != UINT64_C(0)) {
        result = number;
        number &= number - UINT64_C(1);
    }

    return result;
}

int main(void)
{
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    char *newline = strchr(input, '\n');

    if (newline == NULL) {
        if (!feof(stdin)) {
            int character;

            while ((character = getchar()) != '\n' && character != EOF) {
            }

            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    } else {
        *newline = '\0';
    }

    char *start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", highest_power_of_two((uint64_t)value));
    return EXIT_SUCCESS;
}