#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **tuple_to_list(const int *tuple, size_t tuple_len, const char *insert_str, size_t *out_len)
{
    char **list = NULL;
    size_t total = 0U;
    size_t i;
    size_t j;

    if ((tuple == NULL) || (insert_str == NULL) || (out_len == NULL) || (tuple_len == 0U)) {
        return NULL;
    }

    total = tuple_len * 2U;
    list = (char **)malloc(total * sizeof(char *));
    if (list == NULL) {
        return NULL;
    }

    for (i = 0U; i < tuple_len; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char numbuf[32];
        int written;
        size_t idx = i * 2U;

        written = snprintf(numbuf, sizeof(numbuf), "%d", tuple[i]);
        if ((written < 0) || ((size_t)written >= sizeof(numbuf))) {
            for (j = 0U; j < idx; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }

        list[idx] = (char *)malloc((size_t)written + 1U);
        if (list[idx] == NULL) {
            for (j = 0U; j < idx; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(list[idx], numbuf, (size_t)written + 1U);

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        list[idx + 1U] = (char *)malloc(strlen(insert_str) + 1U);
        if (list[idx + 1U] == NULL) {
            for (j = 0U; j <= idx; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memcpy(list[idx + 1U], insert_str, strlen(insert_str) + 1U);
    }

    *out_len = total;
    return list;
}

void free_list(char **list, size_t len)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    for (i = 0U; i < len; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void)
{
    int tuple[] = {1, 5, 7, 4, 6};
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);
    const char *insert_str = "FDF";
    char **result = NULL;
    size_t result_len = 0U;
    size_t i;

    result = tuple_to_list(tuple, tuple_len, insert_str, &result_len);
    if (result == NULL) {
        (void)fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    (void)printf("[");
    for (i = 0U; i < result_len; i++) {
        (void)printf("'%s'", result[i]);
        if (i < (result_len - 1U)) {
            (void)printf(", ");
        }
    }
    (void)printf("]\n");

    free_list(result, result_len);
    return EXIT_SUCCESS;
}