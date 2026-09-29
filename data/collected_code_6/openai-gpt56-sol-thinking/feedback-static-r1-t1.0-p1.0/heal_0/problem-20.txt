#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

bool is_woodall(uint64_t value)
{
    uint64_t n = 1;
    uint64_t power = 2;

    for (;;) {
        uint64_t candidate;

        if (n > UINT64_MAX / power) {
            return false;
        }

        candidate = n * power - 1;

        if (candidate == value) {
            return true;
        }

        if (candidate > value || power > UINT64_MAX / 2) {
            return false;
        }

        ++n;
        power *= 2;
    }
}

int main(void)
{
    char input[128];
    char *start;
    char *end;
    uintmax_t parsed;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > UINT64_MAX) {
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

    if (is_woodall((uint64_t)parsed)) {
        puts("Woodall number");
    } else {
        puts("Not a Woodall number");
    }

    return EXIT_SUCCESS;
}