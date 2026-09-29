#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_tuple(const char **elements, size_t count, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t i;
    size_t *lengths;
    char *result;
    char *position;

    if (elements == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            return NULL;
        }
    }

    if (count > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    lengths = malloc(count * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    delimiter_length = strlen(delimiter);
    total_length = 0;

    for (i = 0; i < count; i++) {
        lengths[i] = strlen(elements[i]);
        if (total_length > SIZE_MAX - lengths[i]) {
            free(lengths);
            return NULL;
        }
        total_length += lengths[i];
        if (i < count - 1) {
            if (total_length > SIZE_MAX - delimiter_length) {
                free(lengths);
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    position = result;
    for (i = 0; i < count; i++) {
        memcpy(position, elements[i], lengths[i]);
        position += lengths[i];
        if (i < count - 1) {
            memcpy(position, delimiter, delimiter_length);
            position += delimiter_length;
        }
    }
    *position = '\0';

    free(lengths);
    return result;
}

int main(void)
{
    const char *tuple[] = { "ID", "is", "4", "UTS" };
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    char *joined;

    joined = concatenate_tuple(tuple, count, "-");
    if (joined == NULL) {
        fprintf(stderr, "Failed to concatenate tuple\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}