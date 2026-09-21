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

        if (current <= 0) {
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

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    return character != EOF || !ferror(stream);
}

static int read_binary_line(FILE *stream,
                            char *buffer,
                            size_t capacity,
                            size_t *length)
{
    if (stream == NULL || buffer == NULL || length == NULL || capacity < 2U) {
        return 0;
    }

    *length = 0;
    buffer[0] = '\0';

    if (fgets(buffer, (int)capacity, stream) == NULL) {
        return 0;
    }

    size_t used = 0;

    while (buffer[used] != '\0' &&
           buffer[used] != '\n' &&
           buffer[used] != '\r') {
        if (buffer[used] != '0' && buffer[used] != '1') {
            return 0;
        }
        ++used;
    }

    if (used == 0U) {
        return 0;
    }

    if (buffer[used] == '\r') {
        if (buffer[used + 1U] == '\n') {
            if (buffer[used + 2U] != '\0') {
                return 0;
            }
        } else if (buffer[used + 1U] != '\0') {
            return 0;
        }
    } else if (buffer[used] == '\n') {
        if (buffer[used + 1U] != '\0') {
            return 0;
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character != '\n' && character != EOF) {
            if (character == '\r') {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                int next = fgetc(stream);

                if (next != '\n' && next != EOF) {
                    if (!discard_line(stream)) {
                        return 0;
                    }
                    return 0;
                }

                if (next == EOF && ferror(stream)) {
                    return 0;
                }
            } else {
                if (!discard_line(stream)) {
                    return 0;
                }
                return 0;
            }
        }

        if (character == EOF && ferror(stream)) {
            return 0;
        }
    }

    buffer[used] = '\0';
    *length = used;
    return 1;
}

int main(void)
{
    const size_t capacity = (size_t)MAX_INPUT_LENGTH + 1U;
    char *input = malloc(capacity);
    size_t length;
    size_t start;
    size_t end;
    int result;

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