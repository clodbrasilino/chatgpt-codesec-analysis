#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *first;
    const char *second;
} Tuple;

char *flatten_tuples(const Tuple *tuples, size_t count, const char *separator)
{
    if (tuples == NULL || separator == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t sep_len = strlen(separator);
    size_t total = 0;

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].first == NULL || tuples[i].second == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len1 = strlen(tuples[i].first);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len2 = strlen(tuples[i].second);
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
    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(tuples[i].first);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, tuples[i].first, len);
        dest += len;

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, separator, sep_len);
        dest += sep_len;

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(tuples[i].second);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, tuples[i].second, len);
        dest += len;

        if (i + 1 < count) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dest, separator, sep_len);
            dest += sep_len;
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