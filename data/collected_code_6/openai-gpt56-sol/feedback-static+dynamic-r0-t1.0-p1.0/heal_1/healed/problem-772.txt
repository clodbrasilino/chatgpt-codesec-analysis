#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            if (ch == EOF && used == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (used + 1 >= capacity) {
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

        buffer[used++] = (char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;

    if (length != NULL) {
        *length = used;
    }

    return 0;
}

static int parse_size(const char *text, size_t *value)
{
    const unsigned char *p = (const unsigned char *)text;
    size_t result = 0;

    while (isspace(*p) != 0) {
        ++p;
    }

    if (*p == '+') {
        ++p;
    }

    if (!isdigit(*p)) {
        return -1;
    }

    do {
        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

        if (result > (SIZE_MAX - digit) / 10) {
            return -1;
        }

        result = result * 10 + digit;
        ++p;
    } while (isdigit(*p));

    while (isspace(*p) != 0) {
        ++p;
    }

    if (*p != '\0') {
        return -1;
    }

    *value = result;
    return 0;
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
        size_t word_length;

        while (str[read_pos] != '\0' &&
               isspace((unsigned char)str[read_pos]) != 0) {
            ++read_pos;
        }

        word_start = read_pos;

        while (str[read_pos] != '\0' &&
               isspace((unsigned char)str[read_pos]) == 0) {
            ++read_pos;
        }

        word_length = read_pos - word_start;

        if (word_length == 0 || word_length != k) {
            size_t copy_end = word_length == 0 ? read_pos : word_start + word_length;
            size_t i;

            for (i = separator_start; i < copy_end; ++i) {
                str[write_pos++] = str[i];
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
    size_t k;
    int status = EXIT_FAILURE;

    if (read_line(&input, NULL) != 0) {
        goto cleanup;
    }

    if (read_line(&length_input, NULL) != 0) {
        goto cleanup;
    }

    if (parse_size(length_input, &k) != 0) {
        goto cleanup;
    }

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