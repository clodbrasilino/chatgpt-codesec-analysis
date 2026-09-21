#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static char *remove_nested_record(const char *tuple)
{
    size_t length;
    char *result;
    size_t read_index;
    size_t write_index = 0;
    size_t depth = 0;

    if (tuple == NULL) {
        errno = EINVAL;
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(tuple);

    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        char character = tuple[read_index];

        if (character == '(') {
            if (depth == 0) {
                result[write_index++] = character;
            }
            ++depth;
        } else if (character == ')') {
            if (depth == 0) {
                free(result);
                errno = EINVAL;
                return NULL;
            }

            --depth;
            if (depth == 0) {
                result[write_index++] = character;
            }
        } else if (depth <= 1) {
            result[write_index++] = character;
        }
    }

    if (depth != 0) {
        free(result);
        errno = EINVAL;
        return NULL;
    }

    result[write_index] = '\0';
    return result;
}

int main(void)
{
    const char *tuple = "(1, (2, 3), 4, (5, (6, 7)))";
    char *result = remove_nested_record(tuple);

    if (result == NULL) {
        perror("remove_nested_record");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}