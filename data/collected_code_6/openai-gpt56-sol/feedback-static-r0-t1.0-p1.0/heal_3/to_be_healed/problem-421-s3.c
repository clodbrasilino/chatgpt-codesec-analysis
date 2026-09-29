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
    size_t delimiter_count;
    size_t delimiters_length;
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

    delimiter_count = count > 0 ? count - 1 : 0;

    if (delimiter_length != 0 &&
        delimiter_count > SIZE_MAX / delimiter_length) {
        return NULL;
    }

    delimiters_length = delimiter_count * delimiter_length;

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
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
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
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
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