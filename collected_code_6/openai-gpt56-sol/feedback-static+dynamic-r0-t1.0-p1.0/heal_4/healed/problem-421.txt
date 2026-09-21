#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *join_tuple(const char *const elements[], size_t count, const char *delimiter)
{
    size_t delimiter_length;
    size_t total_length = 1;
    size_t *lengths = NULL;
    char *result;
    char *position;

    if (delimiter == NULL || (count != 0 && elements == NULL)) {
        return NULL;
    }

    delimiter_length = strlen(delimiter);

    if (count > 1 && delimiter_length > (SIZE_MAX - total_length) / (count - 1)) {
        return NULL;
    }

    total_length += delimiter_length * (count > 0 ? count - 1 : 0);

    if (count != 0) {
        if (count > SIZE_MAX / sizeof(*lengths)) {
            return NULL;
        }

        lengths = malloc(count * sizeof(*lengths));
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL) {
            free(lengths);
            return NULL;
        }

        lengths[i] = strlen(elements[i]);

        if (lengths[i] > SIZE_MAX - total_length) {
            free(lengths);
            return NULL;
        }

        total_length += lengths[i];
    }

    result = malloc(total_length);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    position = result;

    for (size_t i = 0; i < count; ++i) {
        size_t remaining = (size_t)((result + total_length - 1) - position);

        if (lengths[i] > remaining) {
            free(lengths);
            free(result);
            return NULL;
        }

        if (lengths[i] != 0) {
            memcpy(position, elements[i], lengths[i]);
            position += lengths[i];
        }

        if (i + 1 < count) {
            remaining = (size_t)((result + total_length - 1) - position);

            if (delimiter_length > remaining) {
                free(lengths);
                free(result);
                return NULL;
            }

            if (delimiter_length != 0) {
                memcpy(position, delimiter, delimiter_length);
                position += delimiter_length;
            }
        }
    }

    *position = '\0';
    free(lengths);
    return result;
}

int main(void)
{
    const char *tuple[] = {"apple", "banana", "cherry"};
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);
    char *joined = join_tuple(tuple, count, ", ");

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