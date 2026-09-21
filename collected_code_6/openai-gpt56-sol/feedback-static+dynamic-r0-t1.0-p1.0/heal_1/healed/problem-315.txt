#include <ctype.h>
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

    *result = malloc(best_length + 1);
    if (*result == NULL) {
        return 0;
    }

    memcpy(*result, best_start, best_length);
    (*result)[best_length] = '\0';

    return best_length;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        char *new_buffer;
        size_t new_capacity;

        if (length == capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length != 0 && buffer[length - 1] == '\r') {
        --length;
    }

    if (length == capacity) {
        char *new_buffer;

        if (capacity == SIZE_MAX) {
            free(buffer);
            return NULL;
        }

        new_buffer = realloc(buffer, capacity + 1);
        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char *result = NULL;
    int status = 0;

    input = read_line(stdin);
    if (input == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    if (find_first_max_even_word(input, &result) > 0) {
        if (printf("%s\n", result) < 0) {
            status = 1;
        }
    }

    free(result);
    free(input);

    return status;
}