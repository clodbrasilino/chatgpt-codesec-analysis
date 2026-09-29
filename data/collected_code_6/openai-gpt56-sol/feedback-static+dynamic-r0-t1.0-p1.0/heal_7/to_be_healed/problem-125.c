#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 1000000U

static int maximum_difference(const char *binary_string,
                              size_t length,
                              size_t *start,
                              size_t *end)
{
    int maximum = 0;
    int current = 0;
    size_t current_start = 0;

    if (binary_string == NULL || start == NULL || end == NULL) {
        return -1;
    }

    *start = 0;
    *end = 0;

    for (size_t i = 0; i < length; ++i) {
        int value;

        if (binary_string[i] == '0') {
            value = 1;
        } else if (binary_string[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        if (current < 0) {
            current = value;
            current_start = i;
        } else {
            current += value;
        }

        if (current > maximum) {
            maximum = current;
            *start = current_start;
            *end = i;
        }
    }

    return maximum;
}

static int discard_line(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    return character == '\n' || !ferror(stream);
}

static int read_binary_line(FILE *stream,
                            char *buffer,
                            size_t capacity,
                            size_t *length)
{
    size_t used = 0;
    int character;

    if (stream == NULL || buffer == NULL || length == NULL || capacity < 2U) {
        return 0;
    }

    *length = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    return 0;
                }
                break;
            }

            if (next == '\n') {
                break;
            }

            if (!discard_line(stream)) {
                return 0;
            }

            return 0;
        }

        if (character != '0' && character != '1') {
            if (!discard_line(stream)) {
                return 0;
            }

            return 0;
        }

        if (used >= capacity - 1U) {
            if (!discard_line(stream)) {
                return 0;
            }

            return 0;
        }

        buffer[used++] = (char)character;
    }

    if (ferror(stream) || used == 0U) {
        return 0;
    }

    buffer[used] = '\0';
    *length = used;
    return 1;
}

int main(void)
{
    const size_t capacity = (size_t)MAX_INPUT_LENGTH + 1U;
    char *input;
    size_t length;
    size_t start;
    size_t end;
    int result;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (!read_binary_line(stdin, input, capacity, &length)) {
        free(input);
        return EXIT_FAILURE;
    }

    result = maximum_difference(input, length, &start, &end);
    free(input);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}