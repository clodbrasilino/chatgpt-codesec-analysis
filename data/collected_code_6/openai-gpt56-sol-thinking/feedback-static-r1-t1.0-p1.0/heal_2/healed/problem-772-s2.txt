#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(FILE *stream, char **output)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        unsigned char character;
        size_t bytes_read = fread(&character, 1, 1, stream);

        if (bytes_read == 0) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (length == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\0') {
            free(buffer);
            return -1;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *output = buffer;

    return 1;
}

static int parse_length(const char *text, size_t *length)
{
    const char *current;
    char *end;
    uintmax_t value;

    if (text == NULL || length == NULL) {
        return -1;
    }

    current = text;

    while (isspace((unsigned char)*current)) {
        ++current;
    }

    if (*current == '\0' || *current == '-' || *current == '+') {
        return -1;
    }

    errno = 0;
    value = strtoumax(current, &end, 10);

    if (current == end ||
        errno == ERANGE ||
        value == 0 ||
        value > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *length = (size_t)value;
    return 0;
}

static int remove_words_with_length(char *text, size_t length_to_remove)
{
    char *read_position;
    char *write_position;
    int wrote_word = 0;

    if (text == NULL || length_to_remove == 0) {
        return -1;
    }

    read_position = text;
    write_position = text;

    while (*read_position != '\0') {
        char *word_start;
        size_t word_length;

        while (isspace((unsigned char)*read_position)) {
            ++read_position;
        }

        if (*read_position == '\0') {
            break;
        }

        word_start = read_position;

        while (*read_position != '\0' &&
               !isspace((unsigned char)*read_position)) {
            ++read_position;
        }

        word_length = (size_t)(read_position - word_start);

        if (word_length != length_to_remove) {
            if (wrote_word) {
                *write_position++ = ' ';
            }

            while (word_start < read_position) {
                *write_position++ = *word_start++;
            }

            wrote_word = 1;
        }
    }

    *write_position = '\0';
    return 0;
}

int main(void)
{
    char *text = NULL;
    char *length_text = NULL;
    size_t length_to_remove;
    int status;

    status = read_line(stdin, &text);
    if (status != 1) {
        fputs("Failed to read the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_line(stdin, &length_text);
    if (status != 1) {
        fputs("Failed to read the word length.\n", stderr);
        free(text);
        return EXIT_FAILURE;
    }

    if (parse_length(length_text, &length_to_remove) != 0) {
        fputs("Invalid word length.\n", stderr);
        free(length_text);
        free(text);
        return EXIT_FAILURE;
    }

    free(length_text);

    if (remove_words_with_length(text, length_to_remove) != 0) {
        fputs("Failed to process the string.\n", stderr);
        free(text);
        return EXIT_FAILURE;
    }

    if (puts(text) == EOF) {
        free(text);
        return EXIT_FAILURE;
    }

    free(text);
    return EXIT_SUCCESS;
}