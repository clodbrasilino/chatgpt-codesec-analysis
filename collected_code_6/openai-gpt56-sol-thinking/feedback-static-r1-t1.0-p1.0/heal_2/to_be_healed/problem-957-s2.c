#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *read_line(FILE *stream)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0U) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (character == '\0') {
            free(buffer);
            return NULL;
        }

        if (character == '\n') {
            break;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    buffer[length] = '\0';
    return buffer;
}

static unsigned int rightmost_set_bit_position(uint64_t value)
{
    unsigned int position = 0U;

    while (value != UINT64_C(0)) {
        ++position;

        if ((value & UINT64_C(1)) != UINT64_C(0)) {
            return position;
        }

        value >>= 1U;
    }

    return 0U;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    uintmax_t parsed_value;
    unsigned int position;
    int result = EXIT_FAILURE;

    input = read_line(stdin);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    start = input;

    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed_value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed_value > UINT64_MAX) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    position = rightmost_set_bit_position((uint64_t)parsed_value);

    if (printf("%u\n", position) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(input);
    return result;
}