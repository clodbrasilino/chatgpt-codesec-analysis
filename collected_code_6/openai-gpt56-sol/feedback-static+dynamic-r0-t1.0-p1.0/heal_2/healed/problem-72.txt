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

static bool read_int64(int64_t *result)
{
    char buffer[256];
    char *end;
    intmax_t value;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    if (buffer[0] == '\0') {
        return false;
    }

    char *newline = buffer;
    while (*newline != '\0' && *newline != '\n') {
        ++newline;
    }

    if (*newline != '\n') {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return false;
    }

    *newline = '\0';

    errno = 0;
    value = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        return false;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    while ((newline = fgets(buffer, sizeof buffer, stdin)) != NULL) {
        for (char *p = buffer; *p != '\0'; ++p) {
            if (*p != ' ' && *p != '\t' && *p != '\n' &&
                *p != '\r' && *p != '\f' && *p != '\v') {
                return false;
            }
        }
    }

    if (ferror(stdin)) {
        return false;
    }

    *result = (int64_t)value;
    return true;
}

int main(void)
{
    int64_t value;

    if (!read_int64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_difference_of_two_squares(value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}