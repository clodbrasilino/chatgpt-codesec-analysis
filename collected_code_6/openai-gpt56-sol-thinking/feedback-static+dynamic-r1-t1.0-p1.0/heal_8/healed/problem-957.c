#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LIMIT 127U
#define INPUT_CAPACITY (INPUT_LIMIT + 2U)

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

static int read_input_line(char *buffer, size_t capacity)
{
    size_t i;
    size_t length = capacity;
    size_t null_count = 0U;

    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return 0;
    }

    memset(buffer, UCHAR_MAX, capacity);

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    if (ferror(stdin) != 0) {
        return 0;
    }

    for (i = 0U; i < capacity; ++i) {
        if (buffer[i] == '\0') {
            ++null_count;
            length = i;
        }
    }

    if (null_count != 1U) {
        return 0;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return 1;
    }

    if (length > INPUT_LIMIT || feof(stdin) == 0) {
        return 0;
    }

    return 1;
}

int main(void)
{
    char input[INPUT_CAPACITY];
    char *cursor;
    char *end;
    uintmax_t parsed_value;
    uint32_t value;

    if (!read_input_line(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    while (isspace((unsigned char)*cursor) != 0) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || parsed_value > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    value = (uint32_t)parsed_value;

    if (printf("%" PRIu32 "\n",
               get_rightmost_set_bit_position(value)) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}