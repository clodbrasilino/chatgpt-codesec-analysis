#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_first_longest_even_word(const char *text)
{
    const unsigned char *current;
    const unsigned char *best_start = NULL;
    size_t best_length = 0;

    if (text == NULL) {
        return NULL;
    }

    current = (const unsigned char *)text;

    while (*current != '\0') {
        const unsigned char *start;
        size_t length;

        while (*current != '\0' && isspace(*current)) {
            ++current;
        }

        start = current;

        while (*current != '\0' && !isspace(*current)) {
            ++current;
        }

        length = (size_t)(current - start);

        if (length != 0 && length % 2 == 0 && length > best_length) {
            best_start = start;
            best_length = length;
        }
    }

    if (best_start == NULL || best_length > SIZE_MAX - 1) {
        return NULL;
    }

    char *result = malloc(best_length + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, best_start, best_length);
    result[best_length] = '\0';

    return result;
}

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == capacity - 1) {
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

        buffer[length++] = (char)(unsigned char)character;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);
    char *word;

    if (input == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        if (feof(stdin)) {
            return EXIT_SUCCESS;
        }

        fputs("Failed to allocate memory.\n", stderr);
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