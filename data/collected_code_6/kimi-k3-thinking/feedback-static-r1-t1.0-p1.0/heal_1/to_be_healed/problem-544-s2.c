#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *first;
    const char *second;
} Tuple;

static char *flatten_tuple_list(const Tuple *tuples, size_t count, const char *separator)
{
    size_t total_len = 0;
    size_t sep_len;
    size_t i;
    char *result;
    char *ptr;

    if (tuples == NULL || separator == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    sep_len = strlen(separator);

    for (i = 0; i < count; i++) {
        size_t first_len;
        size_t second_len;
        size_t entry_len;

        if (tuples[i].first == NULL || tuples[i].second == NULL) {
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        first_len = strlen(tuples[i].first);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        second_len = strlen(tuples[i].second);

        if (second_len > SIZE_MAX - 4 || first_len > SIZE_MAX - second_len - 4) {
            return NULL;
        }
        entry_len = first_len + second_len + 4;

        if (SIZE_MAX - total_len < entry_len) {
            return NULL;
        }
        total_len += entry_len;

        if (i + 1 < count) {
            if (SIZE_MAX - total_len < sep_len) {
                return NULL;
            }
            total_len += sep_len;
        }
    }

    if (total_len == SIZE_MAX) {
        return NULL;
    }

    result = (char *)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    ptr = result;

    for (i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t first_len = strlen(tuples[i].first);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t second_len = strlen(tuples[i].second);

        *ptr++ = '(';
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ptr, tuples[i].first, first_len);
        ptr += first_len;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ptr, ", ", 2);
        ptr += 2;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ptr, tuples[i].second, second_len);
        ptr += second_len;
        *ptr++ = ')';

        if (i + 1 < count) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ptr, separator, sep_len);
            ptr += sep_len;
        }
    }

    *ptr = '\0';

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