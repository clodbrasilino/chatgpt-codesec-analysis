#include <ctype.h>
#include <errno.h>
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

static bool read_line(char **line, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer = malloc(capacity);
    int ch = EOF;

    if (buffer == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (used == capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin) || (ch == EOF && used == 0U)) {
        free(buffer);
        return false;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return true;
}

static bool parse_uint32(const char *input, size_t length, uint32_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed_value;

    if (memchr(input, '\0', length) != NULL) {
        return false;
    }

    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return false;
    }

    errno = 0;
    parsed_value = strtoumax(start, &end, 10);

    if (start == end || errno != 0 || parsed_value > UINT32_MAX) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *value = (uint32_t)parsed_value;
    return true;
}

int main(void)
{
    char *input = NULL;
    size_t input_length = 0U;
    uint32_t value;

    if (!read_line(&input, &input_length) ||
        !parse_uint32(input, input_length, &value)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    printf("%" PRIu32 "\n", get_rightmost_set_bit_position(value));

    return EXIT_SUCCESS;
}