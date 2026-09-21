#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 65535

typedef struct {
    const char *first;
    const char *second;
} Tuple;

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

static bool safe_copy(char *dest, size_t dest_remaining, const void *src, size_t len)
{
    size_t i;
    const unsigned char *s;
    unsigned char *d;

    if (dest == NULL || src == NULL || len > dest_remaining) {
        return false;
    }

    s = (const unsigned char *)src;
    d = (unsigned char *)dest;

    for (i = 0; i < len; i++) {
        d[i] = s[i];
    }

    return true;
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
            goto fail;
        }
        *ptr++ = '(';
        remaining -= 1;

        if (!safe_copy(ptr, remaining, tuples[i].first, first_len)) {
            goto fail;
        }
        ptr += first_len;
        remaining -= first_len;

        if (remaining < 2) {
            goto fail;
        }
        if (!safe_copy(ptr, remaining, ", ", 2)) {
            goto fail;
        }
        ptr += 2;
        remaining -= 2;

        if (!safe_copy(ptr, remaining, tuples[i].second, second_len)) {
            goto fail;
        }
        ptr += second_len;
        remaining -= second_len;

        if (remaining < 1) {
            goto fail;
        }
        *ptr++ = ')';
        remaining -= 1;

        if (i + 1 < count) {
            if (!safe_copy(ptr, remaining, separator, sep_len)) {
                goto fail;
            }
            ptr += sep_len;
            remaining -= sep_len;
        }
    }

    if (remaining != 0 || (size_t)(ptr - result) != total_len) {
        goto fail;
    }

    *ptr = '\0';

    free(first_lens);
    free(second_lens);

    return result;

fail:
    free(result);
    free(first_lens);
    free(second_lens);
    return NULL;
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