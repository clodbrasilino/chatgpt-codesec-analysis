#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity == 0) {
        size_t initial_capacity = 128;
        char *buffer = malloc(initial_capacity);

        if (buffer == NULL) {
            return -1;
        }

        *line = buffer;
        *capacity = initial_capacity;
    }

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length >= SIZE_MAX - 1) {
            return -1;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *resized;

            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = *capacity * 2;

            if (new_capacity <= length + 1) {
                return -1;
            }

            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return -1;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF) {
        if (ferror(stream)) {
            return -1;
        }

        if (length == 0) {
            return 0;
        }
    }

    (*line)[length] = '\0';
    return 1;
}

static int remove_words_with_length(char *str, size_t k)
{
    size_t read_pos = 0;
    size_t write_pos = 0;

    if (str == NULL) {
        return -1;
    }

    while (str[read_pos] != '\0') {
        size_t segment_start = read_pos;
        size_t word_start;

        while (str[read_pos] != '\0' &&
               isspace((unsigned char)str[read_pos])) {
            ++read_pos;
        }

        word_start = read_pos;

        while (str[read_pos] != '\0' &&
               !isspace((unsigned char)str[read_pos])) {
            ++read_pos;
        }

        if (word_start == read_pos || read_pos - word_start != k) {
            while (segment_start < read_pos) {
                str[write_pos++] = str[segment_start++];
            }
        }
    }

    str[write_pos] = '\0';
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *length_input = NULL;
    size_t input_capacity = 0;
    size_t length_capacity = 0;
    char *end;
    unsigned long long parsed_length;
    size_t k;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input, &input_capacity) != 1) {
        goto cleanup;
    }

    if (read_line(stdin, &length_input, &length_capacity) != 1) {
        goto cleanup;
    }

    errno = 0;
    end = NULL;
    parsed_length = strtoull(length_input, &end, 10);

    if (errno == ERANGE || end == length_input) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed_length > SIZE_MAX) {
        goto cleanup;
    }

    k = (size_t)parsed_length;

    if (remove_words_with_length(input, k) != 0) {
        goto cleanup;
    }

    if (puts(input) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(length_input);
    free(input);
    return status;
}