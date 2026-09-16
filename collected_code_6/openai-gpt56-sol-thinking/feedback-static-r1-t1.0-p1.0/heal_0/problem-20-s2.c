#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_woodall(uint64_t number)
{
    uint64_t power = 2;

    if (number == 0) {
        return false;
    }

    for (uint64_t index = 1; ; ++index) {
        if (index > UINT64_MAX / power) {
            return false;
        }

        uint64_t candidate = index * power - 1;

        if (candidate == number) {
            return true;
        }

        if (candidate > number || power > UINT64_MAX / 2) {
            return false;
        }

        power *= 2;
    }
}

int main(void)
{
    char input[128];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        return EXIT_FAILURE;
    }

    char *start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    uint64_t number = (uint64_t)value;

    printf("%s\n", is_woodall(number) ? "Woodall number" : "Not a Woodall number");

    return EXIT_SUCCESS;
}