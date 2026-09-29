#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity > SIZE_MAX / 2) {
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

static int read_line(FILE *stream, char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;
    unsigned char byte;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (fread(&byte, sizeof(byte), 1, stream) == 1) {
        if (byte == '\n') {
            break;
        }

        if (byte == '\0') {
            free(buffer);
            return -1;
        }

        if (length == capacity - 1) {
            if (grow_buffer(&buffer, &capacity) != 0) {
                free(buffer);
                return -1;
            }
        }

        buffer[length++] = (char)byte;
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
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

    if (best_length != 0) {
        char *word;
        size_t i;

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
    }

    return 0;
}

int main(void)
{
    char *line = NULL;
    char *word = NULL;
    int status = EXIT_SUCCESS;

    if (read_line(stdin, &line) != 0) {
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