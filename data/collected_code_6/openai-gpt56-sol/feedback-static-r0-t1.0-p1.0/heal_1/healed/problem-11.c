#include <stdio.h>
#include <stdlib.h>

char *remove_first_and_last(const char *str, size_t length, char target)
{
    size_t first = length;
    size_t last = length;
    size_t output_length;
    size_t source_index;
    size_t destination_index = 0;
    char *result;

    if (str == NULL || length == SIZE_MAX) {
        return NULL;
    }

    for (source_index = 0; source_index < length; ++source_index) {
        if (str[source_index] == target) {
            if (first == length) {
                first = source_index;
            }
            last = source_index;
        }
    }

    output_length = length;
    if (first != length) {
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

static int read_line(char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;
    int ch;

    if (line == NULL || length == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (used == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ch == EOF && used == 0) {
        free(buffer);
        return 0;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input;
    size_t input_length;
    char target;
    char *result;
    int ch;

    if (!read_line(&input, &input_length)) {
        return EXIT_FAILURE;
    }

    do {
        ch = fgetc(stdin);
    } while (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' ||
             ch == '\v' || ch == '\f');

    if (ch == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    target = (char)ch;
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