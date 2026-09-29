#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UCHAR_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

#define INITIAL_CAPACITY 128U

static bool can_rearrange_without_equal_adjacent(const char *str, size_t length)
{
    /* Possible weaknesses found:
     *  use of undeclared identifier 'UCHAR_MAX'
     *  'UCHAR_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    size_t frequencies[UCHAR_MAX + 1U] = {0};
    size_t max_frequency = 0;

    if (str == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)str[i];

        if (frequencies[character] == SIZE_MAX) {
            return false;
        }

        ++frequencies[character];

        if (frequencies[character] > max_frequency) {
            max_frequency = frequencies[character];
        }
    }

    return max_frequency <= (length / 2U) + (length % 2U);
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF || character == '\n') {
            if (character == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return -1;
                }

                if (used == 0U) {
                    free(buffer);
                    return 0;
                }
            }

            break;
        }

        if (used == capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    if (used > 0U && buffer[used - 1U] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    int status = read_line(stdin, &input, &length);

    if (status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (puts(can_rearrange_without_equal_adjacent(input, length)
                 ? "true"
                 : "false") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}