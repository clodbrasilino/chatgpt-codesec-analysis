#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096U

static size_t bounded_length(const char *str, size_t max_length, int *valid)
{
    size_t length;

    length = strnlen(str, max_length + 1U);
    if (length > max_length) {
        *valid = 0;
        return 0U;
    }
    *valid = 1;
    return length;
}

static int safe_copy(char *dest, size_t dest_size, size_t offset, const char *src, size_t src_length)
{
    if (dest == NULL || src == NULL) {
        return 0;
    }
    if (offset > dest_size || src_length > dest_size - offset) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest + offset, src, src_length);
    return 1;
}

char *concatenate_tuple(const char *const *elements, size_t count, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t offset;
    size_t i;
    size_t *lengths;
    char *result;
    int valid;

    if (elements == NULL || delimiter == NULL || count == 0U) {
        return NULL;
    }

    delimiter_length = bounded_length(delimiter, MAX_STRING_LENGTH, &valid);
    if (!valid) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    lengths = malloc(count * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    total_length = 0U;

    for (i = 0U; i < count; i++) {
        if (elements[i] == NULL) {
            free(lengths);
            return NULL;
        }
        lengths[i] = bounded_length(elements[i], MAX_STRING_LENGTH, &valid);
        if (!valid) {
            free(lengths);
            return NULL;
        }
        if (lengths[i] > SIZE_MAX - total_length) {
            free(lengths);
            return NULL;
        }
        total_length += lengths[i];
    }

    if (delimiter_length != 0U && count - 1U > (SIZE_MAX - total_length) / delimiter_length) {
        free(lengths);
        return NULL;
    }
    total_length += delimiter_length * (count - 1U);

    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    result = malloc(total_length + 1U);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    offset = 0U;

    for (i = 0U; i < count; i++) {
        if (i > 0U && delimiter_length > 0U) {
            if (!safe_copy(result, total_length, offset, delimiter, delimiter_length)) {
                free(result);
                free(lengths);
                return NULL;
            }
            offset += delimiter_length;
        }
        if (lengths[i] > 0U) {
            if (!safe_copy(result, total_length, offset, elements[i], lengths[i])) {
                free(result);
                free(lengths);
                return NULL;
            }
            offset += lengths[i];
        }
    }

    result[offset] = '\0';
    free(lengths);

    return result;
}

int main(void)
{
    const char *tuple[] = {"ID", "is", "4", "UTS"};
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