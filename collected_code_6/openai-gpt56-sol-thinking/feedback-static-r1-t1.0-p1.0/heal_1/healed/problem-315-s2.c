#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    buffer[0] = '\0';

    for (;;) {
        size_t available;
        size_t bytes_read;

        if (capacity - length < 2) {
            size_t new_capacity;
            char *resized;

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

        available = capacity - length;

        if (fgets(buffer + length, (int)available, stdin) == NULL) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        bytes_read = strlen(buffer + length);

        if (bytes_read > 0 &&
            buffer[length + bytes_read - 1] == '\n') {
            length += bytes_read - 1;
            buffer[length] = '\0';

            if (length > 0 && buffer[length - 1] == '\r') {
                buffer[--length] = '\0';
            }

            break;
        }

        length += bytes_read;
    }

    *line = buffer;
    return 0;
}

static int find_first_longest_even_word(const char *text, char **result)
{
    size_t index = 0;
    size_t best_start = 0;
    size_t best_length = 0;
    char *word;
    size_t i;

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

    if (best_length == SIZE_MAX) {
        return -1;
    }

    word = malloc(best_length + 1);
    if (word == NULL) {
        return -1;
    }

    for (i = 0; i < best_length; ++i) {
        word[i] = text[best_start + i];
    }

    word[best_length] = '\0';
    *result = word;

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
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (word != NULL) {
        if (puts(word) == EOF) {
            status = EXIT_FAILURE;
        }
    } else if (puts("No even-length word found.") == EOF) {
        status = EXIT_FAILURE;
    }

cleanup:
    free(word);
    free(line);
    return status;
}