#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length + 1 >= capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int find_first_longest_even_word(const char *text, char **result)
{
    size_t index = 0;
    size_t best_start = 0;
    size_t best_length = 0;
    char *word;

    if (text == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    while (text[index] != '\0') {
        size_t start;
        size_t length;

        while (text[index] != '\0' &&
               isspace((unsigned char)text[index])) {
            ++index;
        }

        start = index;

        while (text[index] != '\0' &&
               !isspace((unsigned char)text[index])) {
            ++index;
        }

        length = index - start;

        if (length > best_length && length % 2 == 0) {
            best_start = start;
            best_length = length;
        }
    }

    if (best_length == 0) {
        return 0;
    }

    word = malloc(best_length + 1);
    if (word == NULL) {
        return -1;
    }

    memcpy(word, text + best_start, best_length);
    word[best_length] = '\0';
    *result = word;

    return 0;
}

int main(void)
{
    char *line = NULL;
    char *word = NULL;

    if (read_line(&line) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_first_longest_even_word(line, &word) != 0) {
        free(line);
        fputs("Failed to find the word.\n", stderr);
        return EXIT_FAILURE;
    }

    if (word != NULL) {
        if (puts(word) == EOF) {
            free(word);
            free(line);
            return EXIT_FAILURE;
        }
    } else if (puts("No even-length word found.") == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(word);
    free(line);
    return EXIT_SUCCESS;
}