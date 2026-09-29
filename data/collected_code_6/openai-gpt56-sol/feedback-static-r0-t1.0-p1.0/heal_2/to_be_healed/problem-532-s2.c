#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UCHAR_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static bool read_line(char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character == EOF || character == '\n') {
            if (character == EOF && used == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)character;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return true;
}

static bool are_permutations(const char *first, size_t first_length,
                             const char *second, size_t second_length)
{
    /* Possible weaknesses found:
     *  use of undeclared identifier 'UCHAR_MAX'
     *  'UCHAR_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    size_t frequencies[UCHAR_MAX + 1] = {0};

    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    for (size_t i = 0; i < first_length; ++i) {
        ++frequencies[(unsigned char)first[i]];
    }

    for (size_t i = 0; i < second_length; ++i) {
        unsigned char character = (unsigned char)second[i];

        if (frequencies[character] == 0) {
            return false;
        }

        --frequencies[character];
    }

    return true;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length = 0;
    size_t second_length = 0;
    int status = EXIT_FAILURE;

    if (!read_line(&first, &first_length)) {
        goto cleanup;
    }

    if (!read_line(&second, &second_length)) {
        goto cleanup;
    }

    if (are_permutations(first, first_length, second, second_length)) {
        if (puts("The strings are permutations of each other.") == EOF) {
            goto cleanup;
        }
    } else {
        if (puts("The strings are not permutations of each other.") == EOF) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(first);
    free(second);
    return status;
}