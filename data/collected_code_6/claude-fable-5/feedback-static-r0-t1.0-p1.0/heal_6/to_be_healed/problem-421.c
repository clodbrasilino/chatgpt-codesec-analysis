#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_ELEMENT_LENGTH 4096
#define MAX_DELIMITER_LENGTH 256

static size_t bounded_length(const char *str, size_t max_length)
{
    size_t length = 0;

    while (length <= max_length && str[length] != '\0') {
        length++;
    }
    return length;
}

static int safe_append(char **position, size_t *remaining,
                       const char *source, size_t length)
{
    if (source == NULL || position == NULL || *position == NULL ||
        remaining == NULL) {
        return -1;
    }
    if (length > *remaining) {
        return -1;
    }
    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*position, source, length);
        *position += length;
        *remaining -= length;
    }
    return 0;
}

char *concatenate_tuple(const char **elements, size_t count,
                        const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t remaining;
    size_t i;
    size_t *element_lengths;
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

    delimiter_length = bounded_length(delimiter, MAX_DELIMITER_LENGTH);
    if (delimiter_length > MAX_DELIMITER_LENGTH) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    element_lengths = malloc(count * sizeof(size_t));
    if (element_lengths == NULL) {
        return NULL;
    }

    total_length = 0;

    for (i = 0; i < count; i++) {
        element_lengths[i] = bounded_length(elements[i], MAX_ELEMENT_LENGTH);
        if (element_lengths[i] > MAX_ELEMENT_LENGTH) {
            free(element_lengths);
            return NULL;
        }
        if (total_length > SIZE_MAX - element_lengths[i]) {
            free(element_lengths);
            return NULL;
        }
        total_length += element_lengths[i];
        if (i < count - 1) {
            if (total_length > SIZE_MAX - delimiter_length) {
                free(element_lengths);
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length == SIZE_MAX) {
        free(element_lengths);
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        free(element_lengths);
        return NULL;
    }

    position = result;
    remaining = total_length;

    for (i = 0; i < count; i++) {
        if (bounded_length(elements[i], MAX_ELEMENT_LENGTH) !=
            element_lengths[i]) {
            free(element_lengths);
            free(result);
            return NULL;
        }
        if (safe_append(&position, &remaining, elements[i],
                        element_lengths[i]) != 0) {
            free(element_lengths);
            free(result);
            return NULL;
        }
        if (i < count - 1) {
            if (safe_append(&position, &remaining, delimiter,
                            delimiter_length) != 0) {
                free(element_lengths);
                free(result);
                return NULL;
            }
        }
    }

    if (remaining != 0) {
        free(element_lengths);
        free(result);
        return NULL;
    }

    *position = '\0';

    free(element_lengths);
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