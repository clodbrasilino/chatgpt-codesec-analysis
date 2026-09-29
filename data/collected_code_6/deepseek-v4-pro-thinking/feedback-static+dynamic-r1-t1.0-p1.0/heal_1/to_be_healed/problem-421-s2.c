#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuple(const char *elements[], size_t count, const char *delimiter) {
    if (elements == NULL && count > 0) {
        return NULL;
    }
    if (delimiter == NULL) {
        delimiter = "";
    }

    size_t total = 1;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delim_len = strlen(delimiter);

    for (size_t i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t elem_len = strlen(elements[i]);
        if (total > SIZE_MAX - elem_len) {
            return NULL;
        }
        total += elem_len;
        if (i < count - 1) {
            if (total > SIZE_MAX - delim_len) {
                return NULL;
            }
            total += delim_len;
        }
    }

    char *result = malloc(total);
    if (result == NULL) {
        return NULL;
    }

    char *dest = result;
    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t elem_len = strlen(elements[i]);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, elements[i], elem_len);
        dest += elem_len;
        if (i < count - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dest, delimiter, delim_len);
            dest += delim_len;
        }
    }
    *dest = '\0';

    return result;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    char *joined = concat_tuple(tuple, 3, ", ");
    if (joined == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);
    free(joined);

    return EXIT_SUCCESS;
}