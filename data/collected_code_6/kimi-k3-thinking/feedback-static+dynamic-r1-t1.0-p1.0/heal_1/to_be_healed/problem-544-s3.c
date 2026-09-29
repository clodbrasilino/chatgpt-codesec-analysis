#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *first;
    const char *second;
} Tuple;

char *flatten_tuple_list(const Tuple *tuples, size_t count, const char *delimiter)
{
    if (tuples == NULL || delimiter == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    const size_t delim_len = strlen(delimiter);
    size_t total_length = 1;

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].first == NULL || tuples[i].second == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(tuples[i].first) + strlen(tuples[i].second) + (2 * delim_len);
    }

    char *result = malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    char *ptr = result;
    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(tuples[i].first);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ptr, tuples[i].first, len);
        ptr += len;

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ptr, delimiter, delim_len);
        ptr += delim_len;

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(tuples[i].second);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(ptr, tuples[i].second, len);
        ptr += len;

        if (i + 1 < count) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ptr, delimiter, delim_len);
            ptr += delim_len;
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