#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint32_t get_rightmost_set_bit_position(uint32_t value)
{
    uint32_t position = 0U;

    while (value != 0U) {
        ++position;

        if ((value & UINT32_C(1)) != 0U) {
            return position;
        }

        value >>= 1U;
    }

    return 0U;
}

static bool read_uint32_line(uint32_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *cursor;
    char *newline;
    uint32_t result = 0U;
    bool has_digit = false;

    if (value == NULL) {
        return false;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    newline = strchr(buffer, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else if (feof(stdin) == 0) {
        return false;
    }

    cursor = buffer;

    while (isspace((unsigned char)*cursor) != 0) {
        ++cursor;
    }

    if (*cursor == '+') {
        ++cursor;
    }

    while (*cursor >= '0' && *cursor <= '9') {
        uint32_t digit = (uint32_t)(*cursor - '0');

        has_digit = true;

        if (result > (UINT32_MAX - digit) / UINT32_C(10)) {
            return false;
        }

        result = result * UINT32_C(10) + digit;
        ++cursor;
    }

    if (!has_digit) {
        return false;
    }

    while (isspace((unsigned char)*cursor) != 0) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return false;
    }

    *value = result;
    return true;
}

int main(void)
{
    uint32_t value;

    if (!read_uint32_line(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", get_rightmost_set_bit_position(value));

    return EXIT_SUCCESS;
}