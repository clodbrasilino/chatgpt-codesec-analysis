#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *join_tuple(const char *const *elements, size_t count, const char *delimiter)
{
    size_t total_length = 0;
    size_t delimiter_length;
    size_t i;
    char *result;
    char *dest;

    if (elements == NULL || delimiter == NULL) {
        return NULL;
    }

    if (count == 0) {
        result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    delimiter_length = strlen(delimiter);

    for (i = 0; i < count; i++) {
        size_t element_length;

        if (elements[i] == NULL) {
            return NULL;
        }

        element_length = strlen(elements[i]);

        if (element_length > SIZE_MAX - total_length) {
            return NULL;
        }
        total_length += element_length;

        if (i + 1 < count) {
            if (delimiter_length > SIZE_MAX - total_length) {
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    dest = result;

    for (i = 0; i < count; i++) {
        size_t element_length = strlen(elements[i]);

        memcpy(dest, elements[i], element_length);
        dest += element_length;

        if (i + 1 < count) {
            memcpy(dest, delimiter, delimiter_length);
            dest += delimiter_length;
        }
    }

    *dest = '\0';

    return result;
}

int main(void)
{
    const char *tuple[] = { "alpha", "beta", "gamma", "delta" };
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = " | ";
    char *joined;

    joined = join_tuple(tuple, count, delimiter);
    if (joined == NULL) {
        fprintf(stderr, "Error: failed to join tuple elements\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);

    free(joined);
    joined = NULL;

    return EXIT_SUCCESS;
}