#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_line(char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    int character;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
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

    if (character == EOF && used == 0) {
        free(buffer);
        return false;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return true;
}

static bool are_permutations(const char *first, size_t first_length,
                             const char *second, size_t second_length)
{
    size_t frequencies[256] = {0};

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
    bool result;
    int status = EXIT_SUCCESS;

    if (!read_line(&first, &first_length) ||
        !read_line(&second, &second_length)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    result = are_permutations(first, first_length, second, second_length);

    if (puts(result
                 ? "The strings are permutations of each other."
                 : "The strings are not permutations of each other.") == EOF) {
        status = EXIT_FAILURE;
    }

    free(first);
    free(second);
    return status;
}