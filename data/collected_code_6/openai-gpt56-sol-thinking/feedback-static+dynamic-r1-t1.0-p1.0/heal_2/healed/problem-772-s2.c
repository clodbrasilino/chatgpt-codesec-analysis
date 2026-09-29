#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int read_line(FILE *stream, char **output)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length;
    ssize_t result;

    if (stream == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    errno = 0;
    result = getline(&buffer, &capacity, stream);

    if (result < 0) {
        free(buffer);

        if (feof(stream)) {
            return 0;
        }

        return -1;
    }

    length = (size_t)result;

    if (memchr(buffer, '\0', length) != NULL) {
        free(buffer);
        return -1;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        --length;
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

static int remove_words_with_length(char *text, size_t k)
{
    char *read_position;
    char *write_position;
    int has_word = 0;

    if (text == NULL || k == 0) {
        return -1;
    }

    read_position = text;
    write_position = text;

    while (*read_position != '\0') {
        char *word_start;
        size_t word_length = 0;

        while (isspace((unsigned char)*read_position)) {
            ++read_position;
        }

        word_start = read_position;

        while (*read_position != '\0' &&
               !isspace((unsigned char)*read_position)) {
            ++read_position;
            ++word_length;
        }

        if (word_length != 0 && word_length != k) {
            if (has_word) {
                *write_position++ = ' ';
            }

            memmove(write_position, word_start, word_length);
            write_position += word_length;
            has_word = 1;
        }
    }

    *write_position = '\0';
    return 0;
}

int main(void)
{
    char *text = NULL;
    char *length_text = NULL;
    size_t k;
    int status;

    status = read_line(stdin, &text);
    if (status != 1) {
        fprintf(stderr, "Failed to read the input string.\n");
        return EXIT_FAILURE;
    }

    status = read_line(stdin, &length_text);
    if (status != 1) {
        fprintf(stderr, "Failed to read the word length.\n");
        free(text);
        return EXIT_FAILURE;
    }

    if (parse_length(length_text, &k) != 0) {
        fprintf(stderr, "Invalid word length.\n");
        free(length_text);
        free(text);
        return EXIT_FAILURE;
    }

    free(length_text);

    if (remove_words_with_length(text, k) != 0) {
        fprintf(stderr, "Failed to process the string.\n");
        free(text);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", text) < 0) {
        free(text);
        return EXIT_FAILURE;
    }

    free(text);
    return EXIT_SUCCESS;
}