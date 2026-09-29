#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static bool are_isomorphic(const char *first, size_t first_length,
                           const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char forward[UCHAR_MAX + 1U] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char reverse[UCHAR_MAX + 1U] = {0};
    bool forward_set[UCHAR_MAX + 1U] = {false};
    bool reverse_set[UCHAR_MAX + 1U] = {false};

    for (size_t i = 0U; i < first_length; ++i) {
        unsigned char source = (unsigned char)first[i];
        unsigned char target = (unsigned char)second[i];

        if ((forward_set[source] && forward[source] != target) ||
            (reverse_set[target] && reverse[target] != source)) {
            return false;
        }

        forward[source] = target;
        reverse[target] = source;
        forward_set[source] = true;
        reverse_set[target] = true;
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