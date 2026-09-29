#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

static int safe_copy(char *dest, size_t dest_size, size_t position,
                     const char *src, size_t src_length)
{
    size_t remaining;

    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (position > dest_size) {
        return -1;
    }
    remaining = dest_size - position;
    if (src_length > remaining) {
        return -1;
    }
    memcpy(dest + position, src, src_length);
    return 0;
}

char *concatenate_tuple(const char **elements, size_t count, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t position;
    size_t i;
    size_t *element_lengths;
    char *result;

    if (elements == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    delimiter_length = strnlen(delimiter, MAX_STRING_LENGTH);
    if (delimiter_length >= MAX_STRING_LENGTH) {
        return NULL;
    }

    element_lengths = malloc(count * sizeof(size_t));
    if (element_lengths == NULL) {
        return NULL;
    }

    total_length = 0;

    for (i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            free(element_lengths);
            return NULL;
        }
        element_lengths[i] = strnlen(elements[i], MAX_STRING_LENGTH);
        if (element_lengths[i] >= MAX_STRING_LENGTH) {
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

    if (total_length >= SIZE_MAX) {
        free(element_lengths);
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        free(element_lengths);
        return NULL;
    }

    position = 0;

    for (i = 0; i < count; i++) {
        if (safe_copy(result, total_length, position,
                      elements[i], element_lengths[i]) != 0) {
            free(element_lengths);
            free(result);
            return NULL;
        }
        position += element_lengths[i];
        if (i < count - 1) {
            if (safe_copy(result, total_length, position,
                          delimiter, delimiter_length) != 0) {
                free(element_lengths);
                free(result);
                return NULL;
            }
            position += delimiter_length;
        }
    }

    if (position > total_length) {
        free(element_lengths);
        free(result);
        return NULL;
    }

    result[position] = '\0';

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