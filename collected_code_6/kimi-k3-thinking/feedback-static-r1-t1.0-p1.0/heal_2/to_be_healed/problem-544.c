#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 1048576

typedef struct {
    const char *first;
    const char *second;
} Tuple;

static size_t bounded_strlen(const char *s, size_t maxlen, int *valid)
{
    size_t len = 0;
    while (len < maxlen) {
        if (s[len] == '\0') {
            *valid = 1;
            return len;
        }
        len++;
    }
    *valid = 0;
    return len;
}

char *flatten_tuples(const Tuple *tuples, size_t count, const char *separator)
{
    if (tuples == NULL || separator == NULL) {
        return NULL;
    }

    int valid = 0;
    size_t sep_len = bounded_strlen(separator, MAX_STRING_LENGTH, &valid);
    if (!valid) {
        return NULL;
    }

    size_t total = 0;

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].first == NULL || tuples[i].second == NULL) {
            return NULL;
        }
        size_t len1 = bounded_strlen(tuples[i].first, MAX_STRING_LENGTH, &valid);
        if (!valid) {
            return NULL;
        }
        size_t len2 = bounded_strlen(tuples[i].second, MAX_STRING_LENGTH, &valid);
        if (!valid) {
            return NULL;
        }
        if (len1 > SIZE_MAX - len2) {
            return NULL;
        }
        if (total > SIZE_MAX - (len1 + len2)) {
            return NULL;
        }
        total += len1 + len2;
    }

    if (count > 0) {
        if (count > SIZE_MAX / 2 + 1) {
            return NULL;
        }
        size_t sep_count = 2 * count - 1;
        if (sep_len > 0 && sep_count > (SIZE_MAX - total) / sep_len) {
            return NULL;
        }
        total += sep_count * sep_len;
    }

    if (total == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    char *dest = result;
    size_t remaining = total;

    for (size_t i = 0; i < count; i++) {
        size_t len = bounded_strlen(tuples[i].first, MAX_STRING_LENGTH, &valid);
        if (!valid || len > remaining) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, tuples[i].first, len);
        dest += len;
        remaining -= len;

        if (sep_len > remaining) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, separator, sep_len);
        dest += sep_len;
        remaining -= sep_len;

        len = bounded_strlen(tuples[i].second, MAX_STRING_LENGTH, &valid);
        if (!valid || len > remaining) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, tuples[i].second, len);
        dest += len;
        remaining -= len;

        if (i + 1 < count) {
            if (sep_len > remaining) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dest, separator, sep_len);
            dest += sep_len;
            remaining -= sep_len;
        }
    }
    *dest = '\0';

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