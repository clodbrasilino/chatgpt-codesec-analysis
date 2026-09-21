#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t find_first_max_even_word(const char *text, char **result)
{
    const char *best_start = NULL;
    size_t best_length = 0;

    if (text == NULL || result == NULL) {
        return 0;
    }

    *result = NULL;

    while (*text != '\0') {
        const char *word_start;
        size_t word_length = 0;

        while (*text != '\0' && isspace((unsigned char)*text)) {
            ++text;
        }

        word_start = text;

        while (*text != '\0' && !isspace((unsigned char)*text)) {
            if (word_length == SIZE_MAX) {
                return 0;
            }

            ++word_length;
            ++text;
        }

        if (word_length != 0 &&
            word_length % 2 == 0 &&
            word_length > best_length) {
            best_start = word_start;
            best_length = word_length;
        }
    }

    if (best_start == NULL || best_length == SIZE_MAX) {
        return 0;
    }

    char *copy = malloc(best_length + 1);
    if (copy == NULL) {
        return 0;
    }

    if (best_length > 0) {
        memcpy(copy, best_start, best_length);
    }
    copy[best_length] = '\0';

    *result = copy;
    return best_length;
}

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
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
            if (new_capacity <= length + 1) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char *result = NULL;
    int status = EXIT_SUCCESS;

    input = read_line(stdin);
    if (input == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (find_first_max_even_word(input, &result) > 0) {
        if (printf("%s\n", result) < 0) {
            status = EXIT_FAILURE;
        }
    }

    free(result);
    free(input);

    return status;
}