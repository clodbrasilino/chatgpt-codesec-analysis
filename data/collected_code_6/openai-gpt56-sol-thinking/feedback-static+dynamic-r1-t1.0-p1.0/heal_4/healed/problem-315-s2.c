#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL || *buffer == NULL) {
        return -1;
    }

    if (*capacity == 0 || *capacity > SIZE_MAX / 2) {
        return -1;
    }

    new_capacity = *capacity * 2;
    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        unsigned char character;
        size_t bytes_read = fread(&character, 1, 1, stdin);

        if (bytes_read == 0) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (character == (unsigned char)'\n') {
            break;
        }

        if (character == (unsigned char)'\0') {
            free(buffer);
            return -1;
        }

        if (length == capacity - 1) {
            if (grow_buffer(&buffer, &capacity) != 0) {
                free(buffer);
                return -1;
            }
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

    if (text == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    while (text[index] != '\0') {
        size_t start;
        size_t length;

        while (text[index] != '\0' &&
               isspace((unsigned char)text[index]) != 0) {
            ++index;
        }

        start = index;

        while (text[index] != '\0' &&
               isspace((unsigned char)text[index]) == 0) {
            ++index;
        }

        length = index - start;

        if (length != 0 && length % 2 == 0 && length > best_length) {
            best_start = start;
            best_length = length;
        }
    }

    if (best_length != 0) {
        char *word;

        if (best_length > SIZE_MAX - 1) {
            return -1;
        }

        word = malloc(best_length + 1);
        if (word == NULL) {
            return -1;
        }

        memcpy(word, text + best_start, best_length);
        word[best_length] = '\0';
        *result = word;
    }

    return 0;
}

int main(void)
{
    char *line = NULL;
    char *word = NULL;
    int status = EXIT_SUCCESS;

    if (read_line(&line) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_first_longest_even_word(line, &word) != 0) {
        fputs("Failed to find the word.\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    if (word != NULL) {
        if (puts(word) == EOF) {
            status = EXIT_FAILURE;
        }
    } else {
        if (puts("No even-length word found.") == EOF) {
            status = EXIT_FAILURE;
        }
    }

    free(word);
    free(line);

    return status;
}