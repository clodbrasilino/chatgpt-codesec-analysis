#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

static int checked_length(const char *str, size_t *out_length)
{
    size_t length;

    if (str == NULL || out_length == NULL) {
        return -1;
    }

    length = strnlen(str, MAX_STRING_LENGTH);
    if (length >= MAX_STRING_LENGTH) {
        return -1;
    }

    *out_length = length;
    return 0;
}

static int safe_copy(char *dest, size_t dest_size, size_t offset,
                     const char *src, size_t src_length)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }

    if (offset > dest_size || src_length > dest_size - offset) {
        return -1;
    }

    memcpy(dest + offset, src, src_length);
    return 0;
}

char *concatenate_tuple(const char **elements, size_t count, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t *element_lengths;
    size_t offset;
    size_t i;
    char *result;

    if (elements == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    if (checked_length(delimiter, &delimiter_length) != 0) {
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
        if (checked_length(elements[i], &element_lengths[i]) != 0) {
            free(element_lengths);
            return NULL;
        }
        if (element_lengths[i] > SIZE_MAX - total_length) {
            free(element_lengths);
            return NULL;
        }
        total_length += element_lengths[i];
        if (i < count - 1) {
            if (delimiter_length > SIZE_MAX - total_length) {
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

    offset = 0;

    for (i = 0; i < count; i++) {
        if (safe_copy(result, total_length, offset,
                      elements[i], element_lengths[i]) != 0) {
            free(result);
            free(element_lengths);
            return NULL;
        }
        offset += element_lengths[i];
        if (i < count - 1) {
            if (safe_copy(result, total_length, offset,
                          delimiter, delimiter_length) != 0) {
                free(result);
                free(element_lengths);
                return NULL;
            }
            offset += delimiter_length;
        }
    }

    result[offset] = '\0';

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
        fprintf(stderr, "Error: concatenation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}