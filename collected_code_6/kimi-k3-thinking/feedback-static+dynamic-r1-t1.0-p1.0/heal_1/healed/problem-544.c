#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH ((size_t)16 * 1024 * 1024)

typedef struct {
    const char *first;
    const char *second;
} Tuple;

static size_t bounded_strnlen(const char *s, size_t maxlen)
{
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

static int measure_string(const char *s, size_t *out_len)
{
    size_t len = bounded_strnlen(s, MAX_STRING_LENGTH + 1);
    if (len > MAX_STRING_LENGTH) {
        return -1;
    }
    *out_len = len;
    return 0;
}

char *flatten_tuples(const Tuple *tuples, size_t count, const char *separator)
{
    if (tuples == NULL || separator == NULL) {
        return NULL;
    }

    size_t sep_len;
    if (measure_string(separator, &sep_len) != 0) {
        return NULL;
    }

    size_t *lengths = NULL;
    if (count > 0) {
        if (count > SIZE_MAX / (2 * sizeof(size_t))) {
            return NULL;
        }
        lengths = malloc(2 * count * sizeof(size_t));
        if (lengths == NULL) {
            return NULL;
        }
    }

    size_t total = 0;
    for (size_t i = 0; i < count; i++) {
        if (tuples[i].first == NULL || tuples[i].second == NULL) {
            free(lengths);
            return NULL;
        }
        size_t len1;
        size_t len2;
        if (measure_string(tuples[i].first, &len1) != 0 ||
            measure_string(tuples[i].second, &len2) != 0) {
            free(lengths);
            return NULL;
        }
        lengths[2 * i] = len1;
        lengths[2 * i + 1] = len2;
        if (len1 > SIZE_MAX - len2) {
            free(lengths);
            return NULL;
        }
        if (total > SIZE_MAX - (len1 + len2)) {
            free(lengths);
            return NULL;
        }
        total += len1 + len2;
    }

    if (count > 0) {
        size_t sep_count = 2 * count - 1;
        if (sep_len > 0 && sep_count > (SIZE_MAX - total) / sep_len) {
            free(lengths);
            return NULL;
        }
        total += sep_count * sep_len;
    }

    if (total == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    char *result = malloc(total + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    char *dest = result;
    size_t remaining = total;
    for (size_t i = 0; i < count; i++) {
        size_t len = lengths[2 * i];
        if (len > remaining) {
            free(result);
            free(lengths);
            return NULL;
        }
        memcpy(dest, tuples[i].first, len);
        dest += len;
        remaining -= len;

        if (sep_len > remaining) {
            free(result);
            free(lengths);
            return NULL;
        }
        memcpy(dest, separator, sep_len);
        dest += sep_len;
        remaining -= sep_len;

        len = lengths[2 * i + 1];
        if (len > remaining) {
            free(result);
            free(lengths);
            return NULL;
        }
        memcpy(dest, tuples[i].second, len);
        dest += len;
        remaining -= len;

        if (i + 1 < count) {
            if (sep_len > remaining) {
                free(result);
                free(lengths);
                return NULL;
            }
            memcpy(dest, separator, sep_len);
            dest += sep_len;
            remaining -= sep_len;
        }
    }
    *dest = '\0';

    free(lengths);
    return result;
}

int main(void)
{
    const Tuple tuples[] = {
        {"one", "two"},
        {"three", "four"},
        {"five", "six"}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    char *flattened = flatten_tuples(tuples, count, ", ");
    if (flattened == NULL) {
        fprintf(stderr, "Error: unable to flatten tuple list\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", flattened);
    free(flattened);

    return EXIT_SUCCESS;
}