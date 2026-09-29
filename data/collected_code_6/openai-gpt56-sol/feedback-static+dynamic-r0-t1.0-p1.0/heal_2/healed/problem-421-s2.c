#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *tuple_join(const char *const elements[],
                 const size_t lengths[],
                 size_t count,
                 const char *delimiter,
                 size_t delimiter_length)
{
    size_t content_length = 0;
    size_t delimiter_count = count > 0 ? count - 1 : 0;
    size_t total_length;
    char *result;
    char *position;
    size_t remaining;

    if ((count > 0 && (elements == NULL || lengths == NULL)) ||
        (delimiter_length > 0 && delimiter == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] > 0 && elements[i] == NULL) {
            return NULL;
        }

        if (lengths[i] > SIZE_MAX - content_length) {
            return NULL;
        }

        content_length += lengths[i];
    }

    if (delimiter_count > 0 &&
        delimiter_length > SIZE_MAX / delimiter_count) {
        return NULL;
    }

    size_t delimiters_length = delimiter_count * delimiter_length;

    if (delimiters_length > SIZE_MAX - content_length ||
        content_length + delimiters_length == SIZE_MAX) {
        return NULL;
    }

    total_length = content_length + delimiters_length + 1;

    result = malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    position = result;
    remaining = total_length;

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] > remaining - 1) {
            free(result);
            return NULL;
        }

        if (lengths[i] > 0) {
            memcpy(position, elements[i], lengths[i]);
            position += lengths[i];
            remaining -= lengths[i];
        }

        if (i + 1 < count) {
            if (delimiter_length > remaining - 1) {
                free(result);
                return NULL;
            }

            if (delimiter_length > 0) {
                memcpy(position, delimiter, delimiter_length);
                position += delimiter_length;
                remaining -= delimiter_length;
            }
        }
    }

    *position = '\0';
    return result;
}

int main(void)
{
    const char *tuple[] = {"apple", "banana", "cherry"};
    const size_t lengths[] = {
        sizeof("apple") - 1,
        sizeof("banana") - 1,
        sizeof("cherry") - 1
    };
    const char delimiter[] = ", ";
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);

    char *joined = tuple_join(tuple,
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