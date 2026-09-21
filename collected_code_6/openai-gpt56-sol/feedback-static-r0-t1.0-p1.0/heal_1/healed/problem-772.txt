#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL) {
            return -1;
        }
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length + 1 >= *capacity) {
            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = *capacity * 2;
            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return -1;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    if (ch == EOF && length == 0) {
        return 0;
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
        size_t separator_start = read_pos;
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

        if (read_pos == word_start) {
            size_t separator_length = read_pos - separator_start;
            memmove(str + write_pos, str + separator_start, separator_length);
            write_pos += separator_length;
        } else if (read_pos - word_start != k) {
            size_t separator_length = word_start - separator_start;
            size_t word_length = read_pos - word_start;

            memmove(str + write_pos, str + separator_start, separator_length);
            write_pos += separator_length;
            memmove(str + write_pos, str + word_start, word_length);
            write_pos += word_length;
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

    if (read_line(&input, &input_capacity) != 1 ||
        read_line(&length_input, &length_capacity) != 1) {
        goto cleanup;
    }

    errno = 0;
    end = NULL;
    parsed_length = strtoull(length_input, &end, 10);

    if (errno != 0 || end == length_input) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
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