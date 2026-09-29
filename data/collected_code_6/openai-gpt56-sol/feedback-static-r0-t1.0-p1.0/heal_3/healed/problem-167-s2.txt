#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

static int next_power_of_two(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > (UINT64_C(1) << 63)) {
        return 0;
    }

    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;

    *result = n + 1;
    return 1;
}

int main(void)
{
    char input[128];
    char *start;
    char *end;
    uintmax_t value;
    uint64_t result;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    if (*start == '-' || *start == '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(start, &end, 10);

    if (end == start) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || value > UINT64_MAX) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!next_power_of_two((uint64_t)value, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}