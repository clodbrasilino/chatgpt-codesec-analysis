#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **concatenate_adjacent(const char **tuple, size_t count, size_t *result_count)
{
    if (tuple == NULL || result_count == NULL || count < 2U) {
        if (result_count != NULL) {
            *result_count = 0U;
        }
        return NULL;
    }

    size_t out_count = count - 1U;
    char **result = calloc(out_count, sizeof(char *));
    if (result == NULL) {
        *result_count = 0U;
        return NULL;
    }

    for (size_t i = 0U; i < out_count; i++) {
        if (tuple[i] == NULL || tuple[i + 1U] == NULL) {
            for (size_t j = 0U; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0U;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len1 = strlen(tuple[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len2 = strlen(tuple[i + 1U]);
        char *combined = malloc(len1 + len2 + 1U);
        if (combined == NULL) {
            for (size_t j = 0U; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0U;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(combined, tuple[i], len1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(combined + len1, tuple[i + 1U], len2);
        combined[len1 + len2] = '\0';
        result[i] = combined;
    }

    *result_count = out_count;
    return result;
}

void free_result(char **result, size_t count)
{
    if (result == NULL) {
        return;
    }
    for (size_t i = 0U; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void)
{
    const char *tuple[] = { "DSP", "IS", "BEST", "FOR", "ALL", "UTS" };
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    size_t result_count = 0U;

    char **result = concatenate_adjacent(tuple, count, &result_count);
    if (result == NULL) {
        fprintf(stderr, "Concatenation failed\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (size_t i = 0U; i < result_count; i++) {
        printf("'%s'", result[i]);
        if (i + 1U < result_count) {
            printf(", ");
        }
    }
    printf(")\n");

    free_result(result, result_count);
    return EXIT_SUCCESS;
}