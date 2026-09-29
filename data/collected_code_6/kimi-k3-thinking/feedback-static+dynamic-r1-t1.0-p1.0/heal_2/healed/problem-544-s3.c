#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    const char *first;
    const char *second;
} Tuple;

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static int safe_memcpy(char **dst, size_t *remaining, const char *src, size_t len)
{
    if (src == NULL || len > *remaining) {
        return -1;
    }
    memcpy(*dst, src, len);
    *dst += len;
    *remaining -= len;
    return 0;
}

char *flatten_tuple_list(const Tuple *tuples, size_t count, const char *delimiter)
{
    if (tuples == NULL || delimiter == NULL) {
        return NULL;
    }

    size_t delim_len = bounded_strlen(delimiter, MAX_STRING_LENGTH + 1);
    if (delim_len > MAX_STRING_LENGTH) {
        return NULL;
    }

    size_t total_length = 1;

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].first == NULL || tuples[i].second == NULL) {
            return NULL;
        }
        size_t first_len = bounded_strlen(tuples[i].first, MAX_STRING_LENGTH + 1);
        size_t second_len = bounded_strlen(tuples[i].second, MAX_STRING_LENGTH + 1);
        if (first_len > MAX_STRING_LENGTH || second_len > MAX_STRING_LENGTH) {
            return NULL;
        }
        size_t pair_len = first_len + second_len + (2 * delim_len);
        if (total_length > SIZE_MAX - pair_len) {
            return NULL;
        }
        total_length += pair_len;
    }

    char *result = malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    char *ptr = result;
    size_t remaining = total_length - 1;

    for (size_t i = 0; i < count; i++) {
        size_t len = bounded_strlen(tuples[i].first, MAX_STRING_LENGTH + 1);
        if (len > MAX_STRING_LENGTH ||
            safe_memcpy(&ptr, &remaining, tuples[i].first, len) != 0) {
            free(result);
            return NULL;
        }

        if (safe_memcpy(&ptr, &remaining, delimiter, delim_len) != 0) {
            free(result);
            return NULL;
        }

        len = bounded_strlen(tuples[i].second, MAX_STRING_LENGTH + 1);
        if (len > MAX_STRING_LENGTH ||
            safe_memcpy(&ptr, &remaining, tuples[i].second, len) != 0) {
            free(result);
            return NULL;
        }

        if (i + 1 < count) {
            if (safe_memcpy(&ptr, &remaining, delimiter, delim_len) != 0) {
                free(result);
                return NULL;
            }
        }
    }
    *ptr = '\0';

    return result;
}

int main(void)
{
    const Tuple tuples[] = {
        {"apple", "red"},
        {"banana", "yellow"},
        {"grape", "purple"},
        {"orange", "orange"}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);

    char *flattened = flatten_tuple_list(tuples, count, ", ");
    if (flattened == NULL) {
        fprintf(stderr, "Failed to flatten tuple list.\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", flattened);
    free(flattened);

    return EXIT_SUCCESS;
}