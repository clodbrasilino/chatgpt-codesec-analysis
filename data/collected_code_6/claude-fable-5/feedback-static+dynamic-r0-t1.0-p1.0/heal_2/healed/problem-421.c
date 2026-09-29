#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

static size_t bounded_length(const char *str, size_t max_length, int *valid)
{
    size_t length;

    length = strnlen(str, max_length + 1);
    if (length > max_length) {
        *valid = 0;
        return 0;
    }
    *valid = 1;
    return length;
}

char *concatenate_tuple(const char **elements, size_t count, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t i;
    size_t *lengths;
    size_t remaining;
    char *result;
    char *position;
    int valid;

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

    delimiter_length = bounded_length(delimiter, MAX_STRING_LENGTH, &valid);
    if (!valid) {
        free(lengths);
        return NULL;
    }

    total_length = 0;

    for (i = 0; i < count; i++) {
        lengths[i] = bounded_length(elements[i], MAX_STRING_LENGTH, &valid);
        if (!valid) {
            free(lengths);
            return NULL;
        }
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
    remaining = total_length;

    for (i = 0; i < count; i++) {
        if (lengths[i] > remaining) {
            free(lengths);
            free(result);
            return NULL;
        }
        memcpy(position, elements[i], lengths[i]);
        position += lengths[i];
        remaining -= lengths[i];
        if (i < count - 1) {
            if (delimiter_length > remaining) {
                free(lengths);
                free(result);
                return NULL;
            }
            memcpy(position, delimiter, delimiter_length);
            position += delimiter_length;
            remaining -= delimiter_length;
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