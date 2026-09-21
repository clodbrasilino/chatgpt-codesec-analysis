#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static char *remove_first_and_last(const char *str, size_t length, char target)
{
    size_t first = SIZE_MAX;
    size_t last = SIZE_MAX;
    size_t output_length = length;
    size_t source_index;
    size_t destination_index = 0;
    char *result;

    if (str == NULL || length == SIZE_MAX) {
        return NULL;
    }

    for (source_index = 0; source_index < length; ++source_index) {
        if (str[source_index] == target) {
            if (first == SIZE_MAX) {
                first = source_index;
            }
            last = source_index;
        }
    }

    if (first != SIZE_MAX) {
        --output_length;
        if (last != first) {
            --output_length;
        }
    }

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(output_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (source_index = 0; source_index < length; ++source_index) {
        if (source_index != first && source_index != last) {
            if (destination_index >= output_length) {
                free(result);
                return NULL;
            }
            result[destination_index++] = str[source_index];
        }
    }

    result[destination_index] = '\0';
    return result;
}

static char *read_line(FILE *stream, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || length == NULL) {
        return NULL;
    }

    *length = 0;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        if (used >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used >= capacity - 1) {
            free(buffer);
            return NULL;
        }

        buffer[used++] = (char)(unsigned char)ch;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *length = used;
    return buffer;
}

int main(void)
{
    char *input;
    char *target_line;
    char *result;
    char target;
    size_t input_length;
    size_t target_length;

    input = read_line(stdin, &input_length);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    target_line = read_line(stdin, &target_length);
    if (target_line == NULL || target_length != 1) {
        free(target_line);
        free(input);
        return EXIT_FAILURE;
    }

    target = target_line[0];
    free(target_line);

    result = remove_first_and_last(input, input_length, target);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}