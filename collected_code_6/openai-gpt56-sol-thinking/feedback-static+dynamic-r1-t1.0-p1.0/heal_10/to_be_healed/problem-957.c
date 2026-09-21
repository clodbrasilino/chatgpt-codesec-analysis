#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_LIMIT 127U
#define INPUT_CAPACITY (INPUT_LIMIT + 1U)

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
    /* Possible weaknesses found:
     *  The scope of the variable 'character' can be reduced. [variableScope]
     */
    int character;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stdin) != 0 || length == 0U) {
                return 0;
            }

            break;
        }

        if (character == '\0' || length >= capacity - 1U) {
            return 0;
        }

        buffer[length++] = (char)character;
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

    input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_input_line(input, INPUT_CAPACITY)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    while (isspace((unsigned char)*cursor) != 0) {
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

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    value = (uint32_t)parsed_value;
    free(input);

    if (printf("%" PRIu32 "\n",
               get_rightmost_set_bit_position(value)) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}