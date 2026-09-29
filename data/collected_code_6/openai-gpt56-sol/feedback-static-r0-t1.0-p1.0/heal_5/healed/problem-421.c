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
    size_t content_length = 0;
    size_t delimiter_count;
    size_t delimiter_bytes;
    size_t allocation_size;
    size_t remaining;
    char *result;
    char *position;

    if ((delimiter == NULL && delimiter_length != 0) ||
        (count != 0 && (elements == NULL || element_lengths == NULL))) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL && element_lengths[i] != 0) {
            return NULL;
        }

        if (element_lengths[i] > SIZE_MAX - content_length) {
            return NULL;
        }

        content_length += element_lengths[i];
    }

    delimiter_count = count > 0 ? count - 1 : 0;

    if (delimiter_count != 0 &&
        delimiter_length > SIZE_MAX / delimiter_count) {
        return NULL;
    }

    delimiter_bytes = delimiter_count * delimiter_length;

    if (delimiter_bytes > SIZE_MAX - content_length) {
        return NULL;
    }

    content_length += delimiter_bytes;

    if (content_length == SIZE_MAX) {
        return NULL;
    }

    allocation_size = content_length + 1;
    result = malloc(allocation_size);
    if (result == NULL) {
        return NULL;
    }

    position = result;
    remaining = allocation_size;

    for (size_t i = 0; i < count; ++i) {
        if (element_lengths[i] != 0) {
            if (element_lengths[i] >= remaining) {
                free(result);
                return NULL;
            }

            memcpy(position, elements[i], element_lengths[i]);
            position += element_lengths[i];
            remaining -= element_lengths[i];
        }

        if (i + 1 < count && delimiter_length != 0) {
            if (delimiter_length >= remaining) {
                free(result);
                return NULL;
            }

            memcpy(position, delimiter, delimiter_length);
            position += delimiter_length;
            remaining -= delimiter_length;
        }
    }

    if (remaining == 0) {
        free(result);
        return NULL;
    }

    *position = '\0';
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