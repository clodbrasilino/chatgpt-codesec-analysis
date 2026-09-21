#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    const char *first;
    const char *second;
} Tuple;

static int safe_strnlen(const char *s, size_t max_len, size_t *out_len)
{
    size_t len = 0;

    if (s == NULL || out_len == NULL) {
        return -1;
    }

    while (len < max_len) {
        if (s[len] == '\0') {
            *out_len = len;
            return 0;
        }
        len++;
    }

    return -1;
}

char *flatten_tuple_list(const Tuple *tuples, size_t count, const char *delimiter)
{
    size_t delim_len;
    size_t total_length = 1;
    char *result;
    char *ptr;
    size_t remaining;

    if (tuples == NULL || delimiter == NULL) {
        return NULL;
    }

    if (safe_strnlen(delimiter, MAX_STRING_LENGTH, &delim_len) != 0) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        size_t first_len;
        size_t second_len;
        size_t pair_len;

        if (tuples[i].first == NULL || tuples[i].second == NULL) {
            return NULL;
        }

        if (safe_strnlen(tuples[i].first, MAX_STRING_LENGTH, &first_len) != 0 ||
            safe_strnlen(tuples[i].second, MAX_STRING_LENGTH, &second_len) != 0) {
            return NULL;
        }

        if (first_len > SIZE_MAX - second_len) {
            return NULL;
        }
        pair_len = first_len + second_len;

        if (delim_len > (SIZE_MAX - pair_len) / 2) {
            return NULL;
        }
        pair_len += 2 * delim_len;

        if (pair_len > SIZE_MAX - total_length) {
            return NULL;
        }
        total_length += pair_len;
    }

    result = malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    ptr = result;
    remaining = total_length;

    for (size_t i = 0; i < count; i++) {
        size_t len;

        if (safe_strnlen(tuples[i].first, MAX_STRING_LENGTH, &len) != 0 ||
            len > remaining - 1) {
            free(result);
            return NULL;
        }
        memcpy(ptr, tuples[i].first, len);
        ptr += len;
        remaining -= len;

        if (delim_len > remaining - 1) {
            free(result);
            return NULL;
        }
        memcpy(ptr, delimiter, delim_len);
        ptr += delim_len;
        remaining -= delim_len;

        if (safe_strnlen(tuples[i].second, MAX_STRING_LENGTH, &len) != 0 ||
            len > remaining - 1) {
            free(result);
            return NULL;
        }
        memcpy(ptr, tuples[i].second, len);
        ptr += len;
        remaining -= len;

        if (i + 1 < count) {
            if (delim_len > remaining - 1) {
                free(result);
                return NULL;
            }
            memcpy(ptr, delimiter, delim_len);
            ptr += delim_len;
            remaining -= delim_len;
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