#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096U

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

        size_t len1 = strnlen(tuple[i], MAX_STRING_LENGTH);
        size_t len2 = strnlen(tuple[i + 1U], MAX_STRING_LENGTH);

        if (len1 >= MAX_STRING_LENGTH || len2 >= MAX_STRING_LENGTH) {
            for (size_t j = 0U; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0U;
            return NULL;
        }

        if (len1 > SIZE_MAX - len2 - 1U) {
            for (size_t j = 0U; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0U;
            return NULL;
        }

        size_t total = len1 + len2 + 1U;
        char *combined = malloc(total);
        if (combined == NULL) {
            for (size_t j = 0U; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0U;
            return NULL;
        }

        memcpy(combined, tuple[i], len1);
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