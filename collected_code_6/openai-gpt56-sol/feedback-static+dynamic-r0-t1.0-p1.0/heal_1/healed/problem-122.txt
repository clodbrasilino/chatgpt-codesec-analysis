#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_nth_smart_number(uint64_t n, uint64_t *result)
{
    if (n == 0 || result == NULL || n > UINT64_MAX / 3) {
        return 0;
    }

    *result = n * 3;
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;
    ssize_t length;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed == 0 || parsed > UINT64_MAX) {
        free(line);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    if (!find_nth_smart_number((uint64_t)parsed, &result)) {
        fputs("The requested smart number is out of range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}