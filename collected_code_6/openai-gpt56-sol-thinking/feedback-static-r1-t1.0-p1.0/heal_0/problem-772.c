#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_line(FILE *stream, char **output)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int character;

    if (buffer == NULL) {
        return -1;
    }

    while ((character = fgetc(stream)) != '\n' && character != EOF) {
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

    if (character == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return -1;
        }

        if (length == 0) {
            free(buffer);
            return 0;
        }
    }

    buffer[length] = '\0';
    *output = buffer;
    return 1;
}

static int parse_length(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || parsed > SIZE_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

int remove_words_with_length(char *string, size_t k)
{
    char *read_position;
    char *write_position;
    int has_output = 0;

    if (string == NULL) {
        return 0;
    }

    read_position = string;
    write_position = string;

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

        if (word_length != k) {
            if (has_output) {
                *write_position++ = ' ';
            }

            memmove(write_position, word_start, word_length);
            write_position += word_length;
            has_output = 1;
        }
    }

    *write_position = '\0';
    return 1;
}

int main(void)
{
    char *string = NULL;
    char *length_text = NULL;
    size_t k;
    int status;

    status = read_line(stdin, &string);
    if (status != 1) {
        return EXIT_FAILURE;
    }

    status = read_line(stdin, &length_text);
    if (status != 1) {
        free(string);
        return EXIT_FAILURE;
    }

    if (!parse_length(length_text, &k)) {
        free(length_text);
        free(string);
        return EXIT_FAILURE;
    }

    free(length_text);

    if (!remove_words_with_length(string, k)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}