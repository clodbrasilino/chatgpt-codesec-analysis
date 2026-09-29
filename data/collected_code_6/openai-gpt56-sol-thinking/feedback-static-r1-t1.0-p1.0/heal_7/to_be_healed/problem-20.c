#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum { INPUT_BUFFER_SIZE = 256 };

static bool read_line(char *buffer)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char discard[INPUT_BUFFER_SIZE];
    char *newline;

    if (fgets(buffer, INPUT_BUFFER_SIZE, stdin) == NULL) {
        return false;
    }

    if (ferror(stdin)) {
        return false;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    while (fgets(discard, sizeof discard, stdin) != NULL) {
        if (strchr(discard, '\n') != NULL) {
            break;
        }
    }

    return false;
}

bool read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];
    const char *cursor;
    uint64_t result = 0;

    if (value == NULL || !read_line(buffer)) {
        return false;
    }

    cursor = buffer;

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '+') {
        ++cursor;
    } else if (*cursor == '-') {
        return false;
    }

    if (*cursor < '0' || *cursor > '9') {
        return false;
    }

    while (*cursor >= '0' && *cursor <= '9') {
        uint64_t digit = (uint64_t)(*cursor - '0');

        if (result > UINT64_MAX / 10 ||
            (result == UINT64_MAX / 10 && digit > UINT64_MAX % 10)) {
            return false;
        }

        result = result * 10 + digit;
        ++cursor;
    }

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return false;
    }

    *value = result;
    return true;
}

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
    uint64_t value;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_woodall(value)) {
        puts("Woodall number");
    } else {
        puts("Not a Woodall number");
    }

    return EXIT_SUCCESS;
}