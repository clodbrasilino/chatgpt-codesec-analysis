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
    size_t content_length = 0;
    size_t delimiter_count = count > 0 ? count - 1 : 0;
    size_t delimiters_length;
    size_t output_length;
    size_t position = 0;
    char *result;

    if ((count > 0 && (elements == NULL || lengths == NULL)) ||
        (delimiter_length > 0 && delimiter == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] > 0 && elements[i] == NULL) {
            return NULL;
        }

        if (content_length > SIZE_MAX - lengths[i]) {
            return NULL;
        }

        content_length += lengths[i];
    }

    if (delimiter_length != 0 &&
        delimiter_count > SIZE_MAX / delimiter_length) {
        return NULL;
    }

    delimiters_length = delimiter_count * delimiter_length;

    if (content_length > SIZE_MAX - delimiters_length) {
        return NULL;
    }

    output_length = content_length + delimiters_length;

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(output_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] > output_length - position) {
            free(result);
            return NULL;
        }

        if (lengths[i] != 0) {
            memcpy(result + position, elements[i], lengths[i]);
            position += lengths[i];
        }

        if (i < delimiter_count) {
            if (delimiter_length > output_length - position) {
                free(result);
                return NULL;
            }

            if (delimiter_length != 0) {
                memcpy(result + position, delimiter, delimiter_length);
                position += delimiter_length;
            }
        }
    }

    if (position != output_length) {
        free(result);
        return NULL;
    }

    result[position] = '\0';
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

    if (puts(joined) == EOF) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}