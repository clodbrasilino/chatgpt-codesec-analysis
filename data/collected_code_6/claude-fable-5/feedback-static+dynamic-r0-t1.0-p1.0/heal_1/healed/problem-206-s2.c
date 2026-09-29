#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **concatenate_adjacent(const char **tuple, size_t count, size_t *result_count)
{
    char **result;
    size_t i;

    if (tuple == NULL || result_count == NULL || count < 2U) {
        if (result_count != NULL) {
            *result_count = 0U;
        }
        return NULL;
    }

    *result_count = count - 1U;
    result = (char **)malloc(*result_count * sizeof(char *));
    if (result == NULL) {
        *result_count = 0U;
        return NULL;
    }

    for (i = 0U; i < *result_count; i++) {
        if (tuple[i] == NULL || tuple[i + 1U] == NULL) {
            size_t j;
            for (j = 0U; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0U;
            return NULL;
        }

        {
            size_t len_a = strlen(tuple[i]);
            size_t len_b = strlen(tuple[i + 1U]);
            size_t len = len_a + len_b + 1U;

            if (len < len_a) {
                size_t j;
                for (j = 0U; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0U;
                return NULL;
            }

            result[i] = (char *)malloc(len);
            if (result[i] == NULL) {
                size_t j;
                for (j = 0U; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0U;
                return NULL;
            }

            memcpy(result[i], tuple[i], len_a);
            memcpy(result[i] + len_a, tuple[i + 1U], len_b);
            result[i][len_a + len_b] = '\0';
        }
    }

    return result;
}

void free_result(char **result, size_t count)
{
    size_t i;

    if (result == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void)
{
    const char *tuple[] = { "DSP ", "IS ", "BEST ", "FOR ", "ALL ", "UTS" };
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    size_t result_count = 0U;
    char **result;
    size_t i;

    result = concatenate_adjacent(tuple, count, &result_count);
    if (result == NULL) {
        fprintf(stderr, "Concatenation failed\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (i = 0U; i < result_count; i++) {
        printf("'%s'", result[i]);
        if (i + 1U < result_count) {
            printf(", ");
        }
    }
    printf(")\n");

    free_result(result, result_count);

    return EXIT_SUCCESS;
}