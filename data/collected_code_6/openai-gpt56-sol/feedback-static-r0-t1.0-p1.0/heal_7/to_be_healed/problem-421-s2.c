#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *tuple_join(const char *const elements[],
                 const size_t element_sizes[],
                 size_t count,
                 const char *delimiter,
                 size_t delimiter_size)
{
    if ((count > 0 && (elements == NULL || element_sizes == NULL)) ||
        (delimiter_size > 0 && delimiter == NULL)) {
        return NULL;
    }

    size_t content_size = 0;

    for (size_t i = 0; i < count; ++i) {
        if (element_sizes[i] > 0 && elements[i] == NULL) {
            return NULL;
        }

        if (element_sizes[i] > SIZE_MAX - content_size) {
            return NULL;
        }
        content_size += element_sizes[i];

        if (i + 1 < count) {
            if (delimiter_size > SIZE_MAX - content_size) {
                return NULL;
            }
            content_size += delimiter_size;
        }
    }

    if (content_size == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(content_size + 1);
    if (result == NULL) {
        return NULL;
    }

    char *destination = result;
    size_t remaining = content_size;

    for (size_t i = 0; i < count; ++i) {
        size_t length = element_sizes[i];

        if (length > remaining) {
            free(result);
            return NULL;
        }

        if (length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(destination, elements[i], length);
            destination += length;
            remaining -= length;
        }

        if (i + 1 < count) {
            if (delimiter_size > remaining) {
                free(result);
                return NULL;
            }

            if (delimiter_size > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(destination, delimiter, delimiter_size);
                destination += delimiter_size;
                remaining -= delimiter_size;
            }
        }
    }

    if (remaining != 0) {
        free(result);
        return NULL;
    }

    *destination = '\0';
    return result;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char cherry[] = "cherry";
    static const char delimiter[] = ", ";

    const char *const tuple[] = {
        apple,
        banana,
        cherry
    };

    const size_t tuple_sizes[] = {
        sizeof apple - 1,
        sizeof banana - 1,
        sizeof cherry - 1
    };

    const size_t count = sizeof tuple / sizeof tuple[0];

    char *joined = tuple_join(tuple,
                              tuple_sizes,
                              count,
                              delimiter,
                              sizeof delimiter - 1);

    if (joined == NULL) {
        fputs("Failed to concatenate tuple elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}