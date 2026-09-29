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

static int safe_copy(char *destination, size_t destination_remaining,
                     const char *source, size_t source_length)
{
    if (destination == NULL || source == NULL) {
        return 0;
    }
    if (source_length > destination_remaining) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(destination, source, source_length);
    return 1;
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
        if (!safe_copy(position, remaining, elements[i], lengths[i])) {
            free(lengths);
            free(result);
            return NULL;
        }
        position += lengths[i];
        remaining -= lengths[i];
        if (i < count - 1) {
            if (!safe_copy(position, remaining, delimiter, delimiter_length)) {
                free(lengths);
                free(result);
                return NULL;
            }
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