#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **concatenate_adjacent(const char *const *tuple, size_t size, size_t *out_size) {
    if (!tuple || !out_size) {
        return NULL;
    }

    if (size < 2) {
        *out_size = 0;
        return NULL;
    }

    *out_size = size - 1;
    char **result = malloc((*out_size) * sizeof(char *));
    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < *out_size; ++i) {
        if (!tuple[i] || !tuple[i + 1]) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len1 = strlen(tuple[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len2 = strlen(tuple[i + 1]);
        
        result[i] = malloc(len1 + len2 + 1);
        if (!result[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], tuple[i], len1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i] + len1, tuple[i + 1], len2 + 1);
    }

    return result;
}

int main(void) {
    const char *input_tuple[] = {"Apple", "Banana", "Cherry", "Date"};
    size_t input_size = sizeof(input_tuple) / sizeof(input_tuple[0]);
    size_t out_size = 0;

    char **concatenated = concatenate_adjacent(input_tuple, input_size, &out_size);

    if (concatenated) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%s\n", concatenated[i]);
            free(concatenated[i]);
        }
        free(concatenated);
    }

    return 0;
}