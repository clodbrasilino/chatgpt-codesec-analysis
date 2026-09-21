#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void cleanup_partial(char **list, size_t count)
{
    size_t j;

    if (list == NULL) {
        return;
    }
    for (j = 0U; j < count; j++) {
        free(list[j]);
    }
    free(list);
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

    insert_len = strlen(insert_str);
    if (insert_len == SIZE_MAX) {
        return NULL;
    }

    list = (char **)calloc(total, sizeof(char *));
    if (list == NULL) {
        return NULL;
    }

    for (i = 0U; i < tuple_len; i++) {
        char numbuf[32];
        int written;
        size_t num_len;
        size_t idx = i * 2U;

        written = snprintf(numbuf, sizeof(numbuf), "%d", tuple[i]);
        if ((written < 0) || ((size_t)written >= sizeof(numbuf))) {
            cleanup_partial(list, idx);
            return NULL;
        }
        num_len = (size_t)written;

        list[idx] = (char *)malloc(num_len + 1U);
        if (list[idx] == NULL) {
            cleanup_partial(list, idx);
            return NULL;
        }
        memcpy(list[idx], numbuf, num_len);
        list[idx][num_len] = '\0';

        list[idx + 1U] = (char *)malloc(insert_len + 1U);
        if (list[idx + 1U] == NULL) {
            cleanup_partial(list, idx + 1U);
            return NULL;
        }
        memcpy(list[idx + 1U], insert_str, insert_len);
        list[idx + 1U][insert_len] = '\0';
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