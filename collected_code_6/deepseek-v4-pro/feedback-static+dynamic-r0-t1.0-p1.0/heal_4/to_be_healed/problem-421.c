#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **concat_elements(const char **tuple, int tuple_size, const char *delimiter, int *result_count) {
    if (tuple == NULL || delimiter == NULL || result_count == NULL || tuple_size <= 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    for (int i = 0; i < tuple_size; i++) {
        if (tuple[i] == NULL) {
            *result_count = 0;
            return NULL;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delim_len = strlen(delimiter);
    size_t *lens = malloc(tuple_size * sizeof(size_t));
    if (lens == NULL) {
        *result_count = 0;
        return NULL;
    }

    for (int i = 0; i < tuple_size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        lens[i] = strlen(tuple[i]);
    }

    int result_size = tuple_size - 1;
    if (result_size <= 0) {
        free(lens);
        *result_count = 0;
        return NULL;
    }

    char **result = malloc(result_size * sizeof(char *));
    if (result == NULL) {
        free(lens);
        *result_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < result_size; i++) {
        size_t combined_len = lens[i] + lens[i + 1] + delim_len;
        if (combined_len < lens[i] || combined_len < lens[i + 1]) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            free(lens);
            *result_count = 0;
            return NULL;
        }

        char *combined = malloc(combined_len + 1);
        if (combined == NULL) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            free(lens);
            *result_count = 0;
            return NULL;
        }

        size_t offset = 0;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(combined + offset, tuple[i], lens[i]);
        offset += lens[i];
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(combined + offset, delimiter, delim_len);
        offset += delim_len;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(combined + offset, tuple[i + 1], lens[i + 1]);
        offset += lens[i + 1];
        combined[offset] = '\0';
        result[count++] = combined;
    }

    free(lens);
    *result_count = count;
    return result;
}

int main(void) {
    const char *tuple[] = {"hello", "world", "foo", "bar"};
    int result_count = 0;
    char **result = concat_elements(tuple, 4, "-", &result_count);

    if (result == NULL) {
        fprintf(stderr, "Failed to concatenate elements\n");
        return 1;
    }

    for (int i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}