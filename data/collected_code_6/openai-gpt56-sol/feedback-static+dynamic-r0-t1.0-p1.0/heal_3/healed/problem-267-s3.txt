#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int sum_odd_squares(uint64_t n, uint64_t *result)
{
    const uint64_t limit = UINT64_C(1903309);

    if (result == NULL || n > limit) {
        return 0;
    }

    *result = n * (UINT64_C(2) * n - UINT64_C(1)) *
              (UINT64_C(2) * n + UINT64_C(1)) / UINT64_C(3);
    return 1;
}

int main(void)
{
    char input[128];
    char *start;
    char *end;
    uintmax_t value;
    uint64_t result;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\n') {
        *end = '\0';
    } else {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
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
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
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

    if (!sum_odd_squares((uint64_t)value, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}