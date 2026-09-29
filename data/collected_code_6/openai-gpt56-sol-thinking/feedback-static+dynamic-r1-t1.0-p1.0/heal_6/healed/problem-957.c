#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_LIMIT 127U

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
    size_t length = 0U;
    int character;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            buffer[length] = '\0';
            return 1;
        }

        if (character == '\0') {
            return 0;
        }

        if (length >= capacity - 1U) {
            while ((character = fgetc(stdin)) != EOF && character != '\n') {
            }

            return 0;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stdin) != 0 || length == 0U) {
        return 0;
    }

    buffer[length] = '\0';
    return 1;
}

int main(void)
{
    char *input;
    char *cursor;
    char *end;
    uintmax_t parsed_value;
    uint32_t value;
    int result = EXIT_FAILURE;

    input = malloc((size_t)INPUT_LIMIT + 1U);
    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_input_line(input, (size_t)INPUT_LIMIT + 1U)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    cursor = input;

    while (isspace((unsigned char)*cursor) != 0) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    errno = 0;
    parsed_value = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || parsed_value > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    value = (uint32_t)parsed_value;

    if (printf("%" PRIu32 "\n",
               get_rightmost_set_bit_position(value)) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(input);
    return result;
}