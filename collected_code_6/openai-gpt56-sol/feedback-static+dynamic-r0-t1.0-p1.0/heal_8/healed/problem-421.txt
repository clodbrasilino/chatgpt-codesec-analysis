#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *join_tuple(const char *const elements[],
                 const size_t lengths[],
                 size_t count,
                 const char *delimiter,
                 size_t delimiter_length)
{
    if ((count != 0 && (elements == NULL || lengths == NULL)) ||
        (delimiter_length != 0 && delimiter == NULL)) {
        return NULL;
    }

    size_t content_length = 0;

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] != 0 && elements[i] == NULL) {
            return NULL;
        }

        if (lengths[i] > SIZE_MAX - content_length) {
            return NULL;
        }
        content_length += lengths[i];

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

    char *destination = result;
    size_t remaining = content_length;

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] != 0) {
            if (lengths[i] > remaining) {
                free(result);
                return NULL;
            }

            memcpy(destination, elements[i], lengths[i]);
            destination += lengths[i];
            remaining -= lengths[i];
        }

        if (i + 1 < count && delimiter_length != 0) {
            if (delimiter_length > remaining) {
                free(result);
                return NULL;
            }

            memcpy(destination, delimiter, delimiter_length);
            destination += delimiter_length;
            remaining -= delimiter_length;
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

    const char *tuple[] = {
        apple,
        banana,
        cherry
    };

    const size_t lengths[] = {
        sizeof(apple) - 1,
        sizeof(banana) - 1,
        sizeof(cherry) - 1
    };

    const size_t count = sizeof(tuple) / sizeof(tuple[0]);

    char *joined = join_tuple(tuple,
                              lengths,
                              count,
                              delimiter,
                              sizeof(delimiter) - 1);

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