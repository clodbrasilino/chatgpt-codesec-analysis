#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096U

static size_t bounded_length(const char *s, size_t max_len)
{
    size_t len = 0U;

    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static int safe_copy(char *dest, size_t dest_size, size_t offset,
                     const char *src, size_t src_len)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (offset > dest_size || src_len > dest_size - offset) {
        return -1;
    }
    memcpy(dest + offset, src, src_len);
    return 0;
}

char *concatenate_tuple(const char *const *elements, size_t count, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t offset;
    size_t i;
    size_t *lengths;
    char *result;

    if (elements == NULL || delimiter == NULL || count == 0U) {
        return NULL;
    }

    if (count > (size_t)-1 / sizeof(size_t)) {
        return NULL;
    }

    delimiter_length = bounded_length(delimiter, MAX_STRING_LENGTH);
    if (delimiter_length == MAX_STRING_LENGTH) {
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
        lengths[i] = bounded_length(elements[i], MAX_STRING_LENGTH);
        if (lengths[i] == MAX_STRING_LENGTH) {
            free(lengths);
            return NULL;
        }
        if (total_length > (size_t)-1 - lengths[i]) {
            free(lengths);
            return NULL;
        }
        total_length += lengths[i];
    }

    if (delimiter_length != 0U &&
        (count - 1U) > ((size_t)-1 - total_length) / delimiter_length) {
        free(lengths);
        return NULL;
    }
    total_length += delimiter_length * (count - 1U);

    if (total_length == (size_t)-1) {
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
            if (safe_copy(result, total_length, offset, delimiter, delimiter_length) != 0) {
                free(result);
                free(lengths);
                return NULL;
            }
            offset += delimiter_length;
        }
        if (lengths[i] > 0U) {
            if (safe_copy(result, total_length, offset, elements[i], lengths[i]) != 0) {
                free(result);
                free(lengths);
                return NULL;
            }
            offset += lengths[i];
        }
    }

    if (offset > total_length) {
        free(result);
        free(lengths);
        return NULL;
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