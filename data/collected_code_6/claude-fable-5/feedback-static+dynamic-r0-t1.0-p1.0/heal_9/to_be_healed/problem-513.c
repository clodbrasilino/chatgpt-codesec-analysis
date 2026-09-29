#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INSERT_LEN 4096U
#define NUMBUF_SIZE 32U

static void cleanup_partial(char **list, size_t count);
static char *dup_buffer(const char *src, size_t len);
static char *int_to_string(int value);
char **tuple_to_list(const int *tuple, size_t tuple_len, const char *insert_str, size_t *out_len);
void free_list(char **list, size_t len);

static void cleanup_partial(char **list, size_t count)
{
    size_t j;

    if (list == NULL) {
        return;
    }
    for (j = 0U; j < count; j++) {
        free(list[j]);
        list[j] = NULL;
    }
    free(list);
}

static char *dup_buffer(const char *src, size_t len)
{
    char *dst;
    size_t alloc_size;

    if (src == NULL) {
        return NULL;
    }
    if (len >= (SIZE_MAX - 1U)) {
        return NULL;
    }
    if (strnlen(src, len) < len) {
        return NULL;
    }
    alloc_size = len + 1U;
    dst = (char *)malloc(alloc_size);
    if (dst == NULL) {
        return NULL;
    }
    if (len > 0U) {
        if (len > (alloc_size - 1U)) {
            free(dst);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst, src, len);
    }
    dst[len] = '\0';
    return dst;
}

static char *int_to_string(int value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char numbuf[NUMBUF_SIZE];
    int written;
    size_t num_len;

    (void)memset(numbuf, 0, sizeof(numbuf));

    written = snprintf(numbuf, sizeof(numbuf), "%d", value);
    if ((written < 0) || ((size_t)written >= sizeof(numbuf))) {
        return NULL;
    }
    num_len = (size_t)written;

    if (num_len >= NUMBUF_SIZE) {
        return NULL;
    }
    if (numbuf[num_len] != '\0') {
        return NULL;
    }

    return dup_buffer(numbuf, num_len);
}

char **tuple_to_list(const int *tuple, size_t tuple_len, const char *insert_str, size_t *out_len)
{
    char **list = NULL;
    size_t total = 0U;
    size_t insert_len = 0U;
    size_t i;

    if ((tuple == NULL) || (insert_str == NULL) || (out_len == NULL) || (tuple_len == 0U)) {
        return NULL;
    }

    if (tuple_len > (SIZE_MAX / 2U)) {
        return NULL;
    }
    total = tuple_len * 2U;

    if (total > (SIZE_MAX / sizeof(char *))) {
        return NULL;
    }

    insert_len = strnlen(insert_str, MAX_INSERT_LEN + 1U);
    if (insert_len > MAX_INSERT_LEN) {
        return NULL;
    }

    list = (char **)calloc(total, sizeof(char *));
    if (list == NULL) {
        return NULL;
    }

    for (i = 0U; i < tuple_len; i++) {
        size_t idx = i * 2U;

        list[idx] = int_to_string(tuple[i]);
        if (list[idx] == NULL) {
            cleanup_partial(list, idx);
            return NULL;
        }

        list[idx + 1U] = dup_buffer(insert_str, insert_len);
        if (list[idx + 1U] == NULL) {
            cleanup_partial(list, idx + 1U);
            return NULL;
        }
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
        list[i] = NULL;
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