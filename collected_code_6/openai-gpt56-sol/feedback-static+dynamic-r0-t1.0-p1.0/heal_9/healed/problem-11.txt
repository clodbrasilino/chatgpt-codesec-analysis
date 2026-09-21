#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static char *remove_first_and_last(const char *str, size_t length, char target)
{
    size_t first = SIZE_MAX;
    size_t last = SIZE_MAX;
    size_t output_length;
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

    output_length = length;

    if (first != SIZE_MAX) {
        --output_length;
        if (last != first) {
            --output_length;
        }
    }

    result = malloc(output_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (source_index = 0; source_index < length; ++source_index) {
        if (source_index != first && source_index != last) {
            result[destination_index++] = str[source_index];
        }
    }

    result[destination_index] = '\0';
    return result;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return 0;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            if (new_capacity <= used + 1) {
                free(buffer);
                return 0;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)ch;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *target_line = NULL;
    char *result = NULL;
    size_t input_length = 0;
    size_t target_length = 0;
    char target;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input, &input_length)) {
        goto cleanup;
    }

    if (!read_line(stdin, &target_line, &target_length)) {
        goto cleanup;
    }

    if (target_length != 1) {
        goto cleanup;
    }

    target = target_line[0];

    result = remove_first_and_last(input, input_length, target);
    if (result == NULL) {
        goto cleanup;
    }

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    free(target_line);
    free(input);
    return status;
}