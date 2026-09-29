#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *join_tuple(const char *const elements[], size_t count, const char *delimiter)
{
    size_t delimiter_length;
    size_t total_length = 1;
    size_t *element_lengths = NULL;
    char *result;
    char *position;

    if (delimiter == NULL || (count != 0 && elements == NULL)) {
        return NULL;
    }

    delimiter_length = strlen(delimiter);

    if (count > SIZE_MAX / sizeof(*element_lengths)) {
        return NULL;
    }

    if (count != 0) {
        element_lengths = malloc(count * sizeof(*element_lengths));
        if (element_lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == NULL) {
            free(element_lengths);
            return NULL;
        }

        element_lengths[i] = strlen(elements[i]);

        if (element_lengths[i] > SIZE_MAX - total_length) {
            free(element_lengths);
            return NULL;
        }
        total_length += element_lengths[i];

        if (i + 1 < count) {
            if (delimiter_length > SIZE_MAX - total_length) {
                free(element_lengths);
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    result = malloc(total_length);
    if (result == NULL) {
        free(element_lengths);
        return NULL;
    }

    position = result;

    for (size_t i = 0; i < count; ++i) {
        if (element_lengths[i] != 0) {
            memcpy(position, elements[i], element_lengths[i]);
            position += element_lengths[i];
        }

        if (i + 1 < count && delimiter_length != 0) {
            memcpy(position, delimiter, delimiter_length);
            position += delimiter_length;
        }
    }

    *position = '\0';
    free(element_lengths);
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