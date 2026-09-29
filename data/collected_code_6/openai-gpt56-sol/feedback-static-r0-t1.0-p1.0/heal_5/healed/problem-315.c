#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t find_first_max_even_word(const char *text, char *result,
                                size_t result_size)
{
    const char *best_start = NULL;
    const char *cursor;
    size_t best_length = 0;

    if (text == NULL || result == NULL || result_size == 0) {
        return 0;
    }

    result[0] = '\0';
    cursor = text;

    while (*cursor != '\0') {
        const char *word_start;
        size_t word_length;

        while (*cursor != '\0' &&
               isspace((unsigned char)*cursor) != 0) {
            ++cursor;
        }

        word_start = cursor;

        while (*cursor != '\0' &&
               isspace((unsigned char)*cursor) == 0) {
            ++cursor;
        }

        word_length = (size_t)(cursor - word_start);

        if (word_length != 0 &&
            word_length % 2 == 0 &&
            word_length > best_length) {
            best_start = word_start;
            best_length = word_length;
        }
    }

    if (best_start == NULL || best_length >= result_size) {
        return 0;
    }

    memmove(result, best_start, best_length);
    result[best_length] = '\0';

    return best_length;
}

static char *read_line(FILE *stream, size_t *line_length)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL || line_length == NULL) {
        return NULL;
    }

    *line_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
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

        ch = getc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length == 0 && feof(stream)) {
        free(buffer);
        return NULL;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line_length = length;

    return buffer;
}

int main(void)
{
    char *input;
    char *result;
    size_t input_length;
    size_t result_size;
    int status = EXIT_SUCCESS;

    input = read_line(stdin, &input_length);
    if (input == NULL) {
        return feof(stdin) && !ferror(stdin)
                   ? EXIT_SUCCESS
                   : EXIT_FAILURE;
    }

    if (input_length == SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    result_size = input_length + 1;
    result = malloc(result_size);
    if (result == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    if (find_first_max_even_word(input, result, result_size) != 0) {
        if (fputs(result, stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
            status = EXIT_FAILURE;
        }
    }

    free(result);
    free(input);

    return status;
}