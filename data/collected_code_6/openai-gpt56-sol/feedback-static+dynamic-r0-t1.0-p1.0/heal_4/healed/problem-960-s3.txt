#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int count_tilings(size_t n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 1;

    if (result == NULL) {
        return -1;
    }

    for (size_t i = 2; i <= n; ++i) {
        if (UINT64_MAX - current < previous) {
            return -1;
        }

        uint64_t next = current + previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

static int read_input(size_t *value)
{
    char buffer[128];
    char *start;
    char *end;
    uintmax_t input;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return -1;
    }

    errno = 0;
    input = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || input > SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        char *p = buffer;

        while (*p != '\0') {
            if (!isspace((unsigned char)*p)) {
                return -1;
            }
            ++p;
        }
    }

    if (ferror(stdin)) {
        return -1;
    }

    *value = (size_t)input;
    return 0;
}

int main(void)
{
    size_t input;
    uint64_t result;

    if (read_input(&input) != 0) {
        return EXIT_FAILURE;
    }

    if (count_tilings(input, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}