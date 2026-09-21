#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *join_tuple(const char *const elements[],
                 const size_t element_lengths[],
                 size_t count,
                 const char *delimiter,
                 size_t delimiter_length,
                 size_t *result_length)
{
    size_t content_length = 0;
    size_t delimiter_count;
    size_t offset = 0;
    char *result;

    if (result_length == NULL ||
        (delimiter == NULL && delimiter_length != 0) ||
        (count != 0 && (elements == NULL || element_lengths == NULL))) {
        return NULL;
    }

    *result_length = 0;

    for (size_t i = 0; i < count; ++i) {
        if ((elements[i] == NULL && element_lengths[i] != 0) ||
            element_lengths[i] > SIZE_MAX - content_length) {
            return NULL;
        }

        content_length += element_lengths[i];
    }

    delimiter_count = count > 0 ? count - 1 : 0;

    if (delimiter_count != 0 &&
        delimiter_length > (SIZE_MAX - content_length) / delimiter_count) {
        return NULL;
    }

    content_length += delimiter_count * delimiter_length;

    if (content_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(content_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t length = element_lengths[i];
        size_t remaining = content_length - offset;

        if (length > remaining) {
            free(result);
            return NULL;
        }

        if (length != 0) {
            memcpy(result + offset, elements[i], length);
            offset += length;
        }

        if (i + 1 < count && delimiter_length != 0) {
            remaining = content_length - offset;

            if (delimiter_length > remaining) {
                free(result);
                return NULL;
            }

            memcpy(result + offset, delimiter, delimiter_length);
            offset += delimiter_length;
        }
    }

    if (offset != content_length) {
        free(result);
        return NULL;
    }

    result[offset] = '\0';
    *result_length = offset;
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
    size_t joined_length = 0;

    char *joined = join_tuple(tuple,
                              lengths,
                              count,
                              delimiter,
                              sizeof delimiter - 1,
                              &joined_length);

    if (joined == NULL) {
        fputs("Failed to concatenate tuple elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fwrite(joined, 1, joined_length, stdout) != joined_length ||
        fputc('\n', stdout) == EOF) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}