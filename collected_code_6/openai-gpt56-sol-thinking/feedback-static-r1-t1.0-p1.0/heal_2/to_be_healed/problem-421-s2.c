#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} string_view;

char *concatenate_tuple(const string_view tuple[], size_t count,
                        string_view delimiter)
{
    size_t total = 1;
    size_t position = 0;
    char *result;

    if ((count > 0 && tuple == NULL) ||
        (delimiter.length > 0 && delimiter.data == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (tuple[i].length > 0 && tuple[i].data == NULL) {
            return NULL;
        }

        if (tuple[i].length > SIZE_MAX - total) {
            return NULL;
        }
        total += tuple[i].length;

        if (i + 1 < count) {
            if (delimiter.length > SIZE_MAX - total) {
                return NULL;
            }
            total += delimiter.length;
        }
    }

    result = malloc(total);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (tuple[i].length > total - 1 - position) {
            free(result);
            return NULL;
        }

        if (tuple[i].length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + position, tuple[i].data, tuple[i].length);
            position += tuple[i].length;
        }

        if (i + 1 < count) {
            if (delimiter.length > total - 1 - position) {
                free(result);
                return NULL;
            }

            if (delimiter.length > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + position, delimiter.data, delimiter.length);
                position += delimiter.length;
            }
        }
    }

    result[position] = '\0';
    return result;
}

int main(void)
{
    const string_view tuple[] = {
        {"apple", sizeof("apple") - 1},
        {"banana", sizeof("banana") - 1},
        {"cherry", sizeof("cherry") - 1}
    };
    const string_view delimiter = {", ", sizeof(", ") - 1};
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);
    char *result = concatenate_tuple(tuple, count, delimiter);
    int status;

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    status = printf("%s\n", result);
    free(result);

    return status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}