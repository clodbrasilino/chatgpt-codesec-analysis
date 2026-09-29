#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool are_isomorphic(const char *first, size_t first_length,
                           const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    size_t alphabet_size = (size_t)UINT8_MAX + 1U;
    unsigned char *first_to_second = calloc(alphabet_size, sizeof(*first_to_second));
    bool *first_mapped = calloc(alphabet_size, sizeof(*first_mapped));
    bool *second_mapped = calloc(alphabet_size, sizeof(*second_mapped));

    if (first_to_second == NULL || first_mapped == NULL || second_mapped == NULL) {
        free(first_to_second);
        free(first_mapped);
        free(second_mapped);
        return false;
    }

    bool result = true;

    for (size_t i = 0; i < first_length; ++i) {
        unsigned char first_char = (unsigned char)first[i];
        unsigned char second_char = (unsigned char)second[i];

        if (first_mapped[first_char]) {
            if (first_to_second[first_char] != second_char) {
                result = false;
                break;
            }
        } else {
            if (second_mapped[second_char]) {
                result = false;
                break;
            }

            first_to_second[first_char] = second_char;
            first_mapped[first_char] = true;
            second_mapped[second_char] = true;
        }
    }

    free(first_to_second);
    free(first_mapped);
    free(second_mapped);

    return result;
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0U;

    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || used == 0U) {
                free(buffer);
                return false;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used == SIZE_MAX - 1U) {
            free(buffer);
            return false;
        }

        if (used + 1U >= capacity) {
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return false;
            }

            size_t new_capacity = capacity * 2U;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)ch;
    }

    if (used > 0U && buffer[used - 1U] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return true;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length = 0U;
    size_t second_length = 0U;

    if (!read_line(stdin, &first, &first_length) ||
        !read_line(stdin, &second, &second_length)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    bool result = are_isomorphic(first, first_length,
                                 second, second_length);

    free(first);
    free(second);

    if (puts(result ? "Isomorphic" : "Not isomorphic") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}