#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *find_first_longest_even_word(const char *text)
{
    const char *word_start = NULL;
    const char *best_start = NULL;
    size_t word_length = 0;
    size_t best_length = 0;

    if (text == NULL) {
        return NULL;
    }

    for (const char *current = text;; ++current) {
        unsigned char character = (unsigned char)*current;

        if (character != '\0' && !isspace(character)) {
            if (word_start == NULL) {
                word_start = current;
            }

            if (word_length == SIZE_MAX) {
                return NULL;
            }

            ++word_length;
        } else {
            if (word_length != 0 &&
                word_length % 2 == 0 &&
                word_length > best_length) {
                best_start = word_start;
                best_length = word_length;
            }

            word_start = NULL;
            word_length = 0;

            if (character == '\0') {
                break;
            }
        }
    }

    if (best_start == NULL || best_length > SIZE_MAX - 1) {
        return NULL;
    }

    char *result = malloc(best_length + 1);
    if (result == NULL) {
        return NULL;
    }

    if (best_length != 0) {
        memcpy(result, best_start, best_length);
    }
    result[best_length] = '\0';

    return result;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = (*capacity == 0) ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return -1;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character = EOF;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    for (;;) {
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        if (grow_buffer(&buffer, &capacity, length + 2) != 0) {
            free(buffer);
            return -1;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (length == SIZE_MAX ||
        grow_buffer(&buffer, &capacity, length + 1) != 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *word = NULL;

    if (read_line(stdin, &input) != 0) {
        fputs("Unable to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    word = find_first_longest_even_word(input);
    free(input);

    if (word == NULL) {
        puts("No even-length word found.");
        return EXIT_SUCCESS;
    }

    puts(word);
    free(word);

    return EXIT_SUCCESS;
}