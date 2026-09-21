#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN ((size_t)4096)

static void cleanup_partial(char **result, size_t filled)
{
    size_t j;

    for (j = 0U; j < filled; j++) {
        free(result[j]);
    }
    free(result);
}

static int safe_copy(char *dest, size_t dest_size, size_t offset,
                     const char *src, size_t src_len)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (offset > dest_size) {
        return -1;
    }
    if (src_len > dest_size - offset) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest + offset, src, src_len);
    return 0;
}

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

    if (count - 1U > SIZE_MAX / sizeof(char *)) {
        *result_count = 0U;
        return NULL;
    }

    *result_count = count - 1U;
    result = (char **)malloc(*result_count * sizeof(char *));
    if (result == NULL) {
        *result_count = 0U;
        return NULL;
    }

    for (i = 0U; i < *result_count; i++) {
        size_t len_a;
        size_t len_b;
        size_t len;

        if (tuple[i] == NULL || tuple[i + 1U] == NULL) {
            cleanup_partial(result, i);
            *result_count = 0U;
            return NULL;
        }

        len_a = strnlen(tuple[i], MAX_STRING_LEN);
        len_b = strnlen(tuple[i + 1U], MAX_STRING_LEN);

        if (len_a >= MAX_STRING_LEN || len_b >= MAX_STRING_LEN) {
            cleanup_partial(result, i);
            *result_count = 0U;
            return NULL;
        }

        if (len_a > SIZE_MAX - len_b || len_a + len_b > SIZE_MAX - 1U) {
            cleanup_partial(result, i);
            *result_count = 0U;
            return NULL;
        }

        len = len_a + len_b + 1U;

        result[i] = (char *)malloc(len);
        if (result[i] == NULL) {
            cleanup_partial(result, i);
            *result_count = 0U;
            return NULL;
        }

        if (len_a > 0U) {
            if (safe_copy(result[i], len - 1U, 0U, tuple[i], len_a) != 0) {
                cleanup_partial(result, i + 1U);
                *result_count = 0U;
                return NULL;
            }
        }

        if (len_b > 0U) {
            if (safe_copy(result[i], len - 1U, len_a, tuple[i + 1U], len_b) != 0) {
                cleanup_partial(result, i + 1U);
                *result_count = 0U;
                return NULL;
            }
        }

        result[i][len_a + len_b] = '\0';
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