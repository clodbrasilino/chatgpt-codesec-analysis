#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer = NULL;
    size_t capacity = 128;
    size_t used = 0;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    if (length != NULL) {
        *length = 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used >= capacity - 1) {
            char *new_buffer;
            size_t new_capacity;

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

        buffer[used++] = (char)(unsigned char)ch;
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
    const unsigned char *p;
    size_t result = 0;

    if (text == NULL || value == NULL) {
        return -1;
    }

    p = (const unsigned char *)text;

    while (*p != '\0' && isspace(*p)) {
        ++p;
    }

    if (*p == '+') {
        ++p;
    }

    if (!isdigit(*p)) {
        return -1;
    }

    do {
        size_t digit = (size_t)(*p - (unsigned char)'0');

        if (result > (SIZE_MAX - digit) / 10) {
            return -1;
        }

        result = result * 10 + digit;
        ++p;
    } while (isdigit(*p));

    while (*p != '\0' && isspace(*p)) {
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
        size_t segment_start = read_pos;
        size_t word_start;
        size_t word_length;

        while (str[read_pos] != '\0' &&
               isspace((unsigned char)str[read_pos])) {
            ++read_pos;
        }

        word_start = read_pos;

        while (str[read_pos] != '\0' &&
               !isspace((unsigned char)str[read_pos])) {
            ++read_pos;
        }

        word_length = read_pos - word_start;

        if (word_length == 0 || word_length != k) {
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
    size_t k = 0;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input, NULL) != 0) {
        goto cleanup;
    }

    if (read_line(stdin, &length_input, NULL) != 0) {
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