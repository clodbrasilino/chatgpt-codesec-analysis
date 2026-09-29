#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 1048576UL

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

static int append_char(char **ptr, size_t *remaining, char c)
{
    if (*remaining < 1) {
        return -1;
    }

    **ptr = c;
    *ptr += 1;
    *remaining -= 1;

    return 0;
}

static int append_bytes(char **ptr, size_t *remaining, const char *src, size_t len)
{
    size_t i;

    if (src == NULL) {
        return -1;
    }

    if (*remaining < len) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        (*ptr)[i] = src[i];
    }

    *ptr += len;
    *remaining -= len;

    return 0;
}

static char *flatten_tuple_list(const Tuple *tuples, size_t count, const char *separator)
{
    size_t total_len = 0;
    size_t sep_len;
    size_t i;
    size_t remaining;
    char *result;
    char *ptr;
    size_t *first_lens = NULL;
    size_t *second_lens = NULL;

    if (tuples == NULL || separator == NULL) {
        return NULL;
    }

    sep_len = bounded_strlen(separator, MAX_STRING_LEN);
    if (sep_len >= MAX_STRING_LEN) {
        return NULL;
    }

    if (count > 0) {
        if (count > SIZE_MAX / sizeof(size_t)) {
            return NULL;
        }

        first_lens = (size_t *)malloc(count * sizeof(size_t));
        if (first_lens == NULL) {
            return NULL;
        }

        second_lens = (size_t *)malloc(count * sizeof(size_t));
        if (second_lens == NULL) {
            free(first_lens);
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

        first_len = bounded_strlen(tuples[i].first, MAX_STRING_LEN);
        if (first_len >= MAX_STRING_LEN) {
            free(first_lens);
            free(second_lens);
            return NULL;
        }

        second_len = bounded_strlen(tuples[i].second, MAX_STRING_LEN);
        if (second_len >= MAX_STRING_LEN) {
            free(first_lens);
            free(second_lens);
            return NULL;
        }

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

        first_lens[i] = first_len;
        second_lens[i] = second_len;
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

        if (append_char(&ptr, &remaining, '(') != 0) {
            goto copy_fail;
        }

        if (append_bytes(&ptr, &remaining, tuples[i].first, first_len) != 0) {
            goto copy_fail;
        }

        if (append_bytes(&ptr, &remaining, ", ", 2) != 0) {
            goto copy_fail;
        }

        if (append_bytes(&ptr, &remaining, tuples[i].second, second_len) != 0) {
            goto copy_fail;
        }

        if (append_char(&ptr, &remaining, ')') != 0) {
            goto copy_fail;
        }

        if (i + 1 < count) {
            if (append_bytes(&ptr, &remaining, separator, sep_len) != 0) {
                goto copy_fail;
            }
        }
    }

    if (remaining != 0) {
        goto copy_fail;
    }

    *ptr = '\0';

    free(first_lens);
    free(second_lens);

    return result;

copy_fail:
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