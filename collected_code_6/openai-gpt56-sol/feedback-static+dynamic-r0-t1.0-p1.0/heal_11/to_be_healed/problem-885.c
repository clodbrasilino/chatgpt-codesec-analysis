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

    int forward[UINT8_MAX + 1U];
    int reverse[UINT8_MAX + 1U];

    for (size_t i = 0U; i < UINT8_MAX + 1U; ++i) {
        forward[i] = -1;
        reverse[i] = -1;
    }

    for (size_t i = 0U; i < first_length; ++i) {
        const unsigned char source = (unsigned char)first[i];
        const unsigned char target = (unsigned char)second[i];

        if ((forward[source] != -1 && forward[source] != (int)target) ||
            (reverse[target] != -1 && reverse[target] != (int)source)) {
            return false;
        }

        forward[source] = (int)target;
        reverse[target] = (int)source;
    }

    return true;
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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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

            const size_t new_capacity = capacity * 2U;
            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
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

    const bool result = are_isomorphic(first, first_length,
                                       second, second_length);

    free(first);
    free(second);

    if (puts(result ? "Isomorphic" : "Not isomorphic") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}