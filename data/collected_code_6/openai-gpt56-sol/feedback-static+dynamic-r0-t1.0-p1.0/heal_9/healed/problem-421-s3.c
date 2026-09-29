#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *join_tuple(const char *const elements[],
                 const size_t element_lengths[],
                 size_t count,
                 const char *delimiter,
                 size_t delimiter_length)
{
    if ((count != 0 && (elements == NULL || element_lengths == NULL)) ||
        (delimiter_length != 0 && delimiter == NULL)) {
        return NULL;
    }

    size_t content_length = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t length = element_lengths[i];

        if (length != 0 && elements[i] == NULL) {
            return NULL;
        }

        if (length > SIZE_MAX - content_length) {
            return NULL;
        }

        content_length += length;

        if (i + 1 < count) {
            if (delimiter_length > SIZE_MAX - content_length) {
                return NULL;
            }

            content_length += delimiter_length;
        }
    }

    if (content_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(content_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t length = element_lengths[i];

        if (length > content_length - offset) {
            free(result);
            return NULL;
        }

        if (length != 0) {
            memcpy(result + offset, elements[i], length);
            offset += length;
        }

        if (i + 1 < count) {
            if (delimiter_length > content_length - offset) {
                free(result);
                return NULL;
            }

            if (delimiter_length != 0) {
                memcpy(result + offset, delimiter, delimiter_length);
                offset += delimiter_length;
            }
        }
    }

    if (offset != content_length) {
        free(result);
        return NULL;
    }

    result[offset] = '\0';
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

    const size_t lengths[] = {
        sizeof apple - 1,
        sizeof banana - 1,
        sizeof cherry - 1
    };

    const size_t count = sizeof tuple / sizeof tuple[0];

    char *joined = join_tuple(tuple,
                              lengths,
                              count,
                              delimiter,
                              sizeof delimiter - 1);

    if (joined == NULL) {
        fputs("Failed to concatenate tuple elements.\n", stderr);
        return EXIT_FAILURE;
    }

    int status = puts(joined) == EOF ? EXIT_FAILURE : EXIT_SUCCESS;

    free(joined);
    return status;
}