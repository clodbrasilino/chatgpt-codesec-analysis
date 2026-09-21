#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int move_numbers_to_end(char *str, size_t length)
{
    char *result;
    size_t write_index = 0;

    if (str == NULL || length == SIZE_MAX) {
        return -1;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char c = (unsigned char)str[i];

        if (!isdigit(c)) {
            result[write_index++] = str[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char c = (unsigned char)str[i];

        if (isdigit(c)) {
            result[write_index++] = str[i];
        }
    }

    result[write_index] = '\0';

    for (size_t i = 0; i <= length; ++i) {
        str[i] = result[i];
    }

    free(result);
    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *temporary;

    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    temporary = realloc(*buffer, new_capacity);
    if (temporary == NULL) {
        return -1;
    }

    *buffer = temporary;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer;
    size_t capacity = 128;
    size_t used = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return -1;
            }

            break;
        }

        if (used > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        if (grow_buffer(&buffer, &capacity, used + 2) != 0) {
            free(buffer);
            return -1;
        }

        buffer[used++] = (char)(unsigned char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;

    if (read_line(stdin, &input, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (move_numbers_to_end(input, length) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}