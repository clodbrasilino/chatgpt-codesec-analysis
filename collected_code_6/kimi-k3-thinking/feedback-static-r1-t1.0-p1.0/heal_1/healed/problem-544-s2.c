#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 65535

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

static char *flatten_tuple_list(const Tuple *tuples, size_t count, const char *separator)
{
    size_t total_len = 0;
    size_t sep_len;
    size_t i;
    char *result;
    char *ptr;
    size_t *first_lens = NULL;
    size_t *second_lens = NULL;
    size_t remaining;

    if (tuples == NULL || separator == NULL) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    sep_len = bounded_strlen(separator, (size_t)MAX_STRING_LENGTH + 1);
    if (sep_len > MAX_STRING_LENGTH) {
        return NULL;
    }

    if (count > 0) {
        first_lens = (size_t *)malloc(count * sizeof(size_t));
        second_lens = (size_t *)malloc(count * sizeof(size_t));
        if (first_lens == NULL || second_lens == NULL) {
            free(first_lens);
            free(second_lens);
            return NULL;
        }
    }

    for (i = 0; i < count; i++) {
        size_t first_len;
        size_t second_len;
        size_t entry_len;

        if (tuples[i].first == NULL || tuples[i].second == NULL) {
            free(first_lens);
            free(second_lens);
            return NULL;
        }

        first_len = bounded_strlen(tuples[i].first, (size_t)MAX_STRING_LENGTH + 1);
        if (first_len > MAX_STRING_LENGTH) {
            free(first_lens);
            free(second_lens);
            return NULL;
        }

        second_len = bounded_strlen(tuples[i].second, (size_t)MAX_STRING_LENGTH + 1);
        if (second_len > MAX_STRING_LENGTH) {
            free(first_lens);
            free(second_lens);
            return NULL;
        }

        first_lens[i] = first_len;
        second_lens[i] = second_len;

        if (second_len > SIZE_MAX - 4 || first_len > SIZE_MAX - second_len - 4) {
            free(first_lens);
            free(second_lens);
            return NULL;
        }
        entry_len = first_len + second_len + 4;

        if (SIZE_MAX - total_len < entry_len) {
            free(first_lens);
            free(second_lens);
            return NULL;
        }
        total_len += entry_len;

        if (i + 1 < count) {
            if (SIZE_MAX - total_len < sep_len) {
                free(first_lens);
                free(second_lens);
                return NULL;
            }
            total_len += sep_len;
        }
    }

    if (total_len == SIZE_MAX) {
        free(first_lens);
        free(second_lens);
        return NULL;
    }

    result = (char *)malloc(total_len + 1);
    if (result == NULL) {
        free(first_lens);
        free(second_lens);
        return NULL;
    }

    ptr = result;
    remaining = total_len;

    for (i = 0; i < count; i++) {
        size_t first_len = first_lens[i];
        size_t second_len = second_lens[i];

        if (remaining < 1) {
            free(result);
            free(first_lens);
            free(second_lens);
            return NULL;
        }
        *ptr++ = '(';
        remaining -= 1;

        if (first_len > remaining) {
            free(result);
            free(first_lens);
            free(second_lens);
            return NULL;
        }
        memcpy(ptr, tuples[i].first, first_len);
        ptr += first_len;
        remaining -= first_len;

        if (remaining < 2) {
            free(result);
            free(first_lens);
            free(second_lens);
            return NULL;
        }
        memcpy(ptr, ", ", 2);
        ptr += 2;
        remaining -= 2;

        if (second_len > remaining) {
            free(result);
            free(first_lens);
            free(second_lens);
            return NULL;
        }
        memcpy(ptr, tuples[i].second, second_len);
        ptr += second_len;
        remaining -= second_len;

        if (remaining < 1) {
            free(result);
            free(first_lens);
            free(second_lens);
            return NULL;
        }
        *ptr++ = ')';
        remaining -= 1;

        if (i + 1 < count) {
            if (sep_len > remaining) {
                free(result);
                free(first_lens);
                free(second_lens);
                return NULL;
            }
            memcpy(ptr, separator, sep_len);
            ptr += sep_len;
            remaining -= sep_len;
        }
    }

    *ptr = '\0';

    free(first_lens);
    free(second_lens);

    return result;
}

int main(void)
{
    Tuple tuples[] = {
        {"apple", "red"},
        {"banana", "yellow"},
        {"grape", "purple"}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    char *flattened;

    flattened = flatten_tuple_list(tuples, count, ", ");
    if (flattened == NULL) {
        fprintf(stderr, "Failed to flatten tuple list\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", flattened);
    free(flattened);
    flattened = NULL;

    return EXIT_SUCCESS;
}