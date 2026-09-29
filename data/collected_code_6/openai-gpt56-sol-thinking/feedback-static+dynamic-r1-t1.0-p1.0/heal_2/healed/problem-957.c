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

static int read_input_line(char **line)
{
    char *buffer;
    size_t length = 0U;
    int ch;

    if (line == NULL) {
        return 0;
    }

    buffer = malloc(INPUT_LIMIT + 1U);
    if (buffer == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (ch == '\0' || length >= INPUT_LIMIT) {
            free(buffer);
            return 0;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0U)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *cursor;
    char *end;
    uintmax_t parsed_value;
    uint32_t value;

    if (!read_input_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || parsed_value > UINT32_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    value = (uint32_t)parsed_value;
    free(input);

    printf("%" PRIu32 "\n", get_rightmost_set_bit_position(value));

    return EXIT_SUCCESS;
}