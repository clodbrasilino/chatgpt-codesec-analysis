#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 256

static bool read_uint64_line(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];
    unsigned char *cursor;
    char *newline;
    uint64_t result = UINT64_C(0);
    size_t null_count = 0;

    if (value == NULL) {
        return false;
    }

    memset(buffer, 0xA5, sizeof(buffer));

    if (fgets(buffer, sizeof(buffer), stdin) == NULL || ferror(stdin)) {
        return false;
    }

    for (size_t i = 0; i < sizeof(buffer); ++i) {
        if (buffer[i] == '\0') {
            ++null_count;
        }
    }

    if (null_count != 1) {
        return false;
    }

    newline = strchr(buffer, '\n');

    if (newline != NULL) {
        *newline = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    } else if (strlen(buffer) == sizeof(buffer) - 1) {
        return false;
    }

    cursor = (unsigned char *)buffer;

    while (*cursor != '\0' && isspace(*cursor)) {
        ++cursor;
    }

    if (*cursor == '-') {
        return false;
    }

    if (*cursor == '+') {
        ++cursor;
    }

    if (*cursor < '0' || *cursor > '9') {
        return false;
    }

    while (*cursor >= '0' && *cursor <= '9') {
        uint64_t digit = (uint64_t)(*cursor - '0');

        if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
            return false;
        }

        result = result * UINT64_C(10) + digit;
        ++cursor;
    }

    while (*cursor != '\0' && isspace(*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return false;
    }

    *value = result;
    return true;
}

static bool is_woodall(uint64_t number)
{
    for (uint64_t index = UINT64_C(1); index < UINT64_C(64); ++index) {
        if (index > (UINT64_MAX >> index)) {
            break;
        }

        uint64_t candidate = (index << index) - UINT64_C(1);

        if (candidate == number) {
            return true;
        }

        if (candidate > number) {
            break;
        }
    }

    return false;
}

int main(void)
{
    uint64_t value;

    if (!read_uint64_line(&value)) {
        return EXIT_FAILURE;
    }

    if (fputs(is_woodall(value)
                  ? "Woodall number\n"
                  : "Not a Woodall number\n",
              stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}