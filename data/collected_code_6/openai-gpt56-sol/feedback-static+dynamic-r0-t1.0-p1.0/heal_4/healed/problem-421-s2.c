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
    size_t delimiter_count;
    size_t delimiter_bytes;
    size_t total_length;
    size_t offset = 0;
    char *result;

    if ((count != 0 && (elements == NULL || lengths == NULL)) ||
        (delimiter_length != 0 && delimiter == NULL)) {
        return NULL;
    }

    delimiter_count = count > 0 ? count - 1 : 0;

    if (delimiter_count != 0 &&
        delimiter_length > SIZE_MAX / delimiter_count) {
        return NULL;
    }

    delimiter_bytes = delimiter_count * delimiter_length;

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] != 0 && elements[i] == NULL) {
            return NULL;
        }

        if (lengths[i] > SIZE_MAX - content_length) {
            return NULL;
        }

        content_length += lengths[i];
    }

    if (delimiter_bytes > SIZE_MAX - content_length) {
        return NULL;
    }

    total_length = content_length + delimiter_bytes;

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] != 0) {
            if (offset > total_length ||
                lengths[i] > total_length - offset) {
                free(result);
                return NULL;
            }

            memcpy(result + offset, elements[i], lengths[i]);
            offset += lengths[i];
        }

        if (i + 1 < count && delimiter_length != 0) {
            if (offset > total_length ||
                delimiter_length > total_length - offset) {
                free(result);
                return NULL;
            }

            memcpy(result + offset, delimiter, delimiter_length);
            offset += delimiter_length;
        }
    }

    if (offset != total_length) {
        free(result);
        return NULL;
    }

    result[offset] = '\0';
    return result;
}

int main(void)
{
    const char *tuple[] = {
        "apple",
        "banana",
        "cherry"
    };
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