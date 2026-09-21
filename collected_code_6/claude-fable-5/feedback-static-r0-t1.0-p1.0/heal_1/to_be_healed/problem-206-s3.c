#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **concat_adjacent(const char **tuple, size_t n, size_t *out_n)
{
    char **result;
    size_t i;

    if (tuple == NULL || out_n == NULL || n < 2) {
        if (out_n != NULL) {
            *out_n = 0;
        }
        return NULL;
    }

    result = calloc(n - 1, sizeof(char *));
    if (result == NULL) {
        *out_n = 0;
        return NULL;
    }

    for (i = 0; i < n - 1; i++) {
        size_t len1;
        size_t len2;

        if (tuple[i] == NULL || tuple[i + 1] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *out_n = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len1 = strlen(tuple[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len2 = strlen(tuple[i + 1]);

        result[i] = malloc(len1 + len2 + 1U);
        if (result[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *out_n = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], tuple[i], len1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i] + len1, tuple[i + 1], len2 + 1U);
    }

    *out_n = n - 1;
    return result;
}

void free_result(char **result, size_t n)
{
    size_t i;

    if (result == NULL) {
        return;
    }
    for (i = 0; i < n; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void)
{
    const char *tuple[] = { "DSP ", "IS ", "BEST ", "FOR ", "ALL ", "UTS" };
    size_t n = sizeof(tuple) / sizeof(tuple[0]);
    size_t out_n = 0;
    size_t i;
    char **result;

    result = concat_adjacent(tuple, n, &out_n);
    if (result == NULL) {
        fprintf(stderr, "Concatenation failed\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (i = 0; i < out_n; i++) {
        printf("'%s'", result[i]);
        if (i + 1 < out_n) {
            printf(", ");
        }
    }
    printf(")\n");

    free_result(result, out_n);
    return EXIT_SUCCESS;
}