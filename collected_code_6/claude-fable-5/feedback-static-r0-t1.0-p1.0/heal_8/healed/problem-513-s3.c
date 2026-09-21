#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096U

static char *duplicate_string(const char *src)
{
    size_t len;
    size_t alloc_size;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }

    alloc_size = len + 1U;

    copy = malloc(alloc_size);
    if (copy == NULL) {
        return NULL;
    }

    if (len > 0U) {
        memcpy(copy, src, len);
    }
    copy[len] = '\0';
    return copy;
}

static void free_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0U; i < count; i++) {
        free(list[i]);
        list[i] = NULL;
    }
    free(list);
}

static char **tuple_to_list(const char *const *tuple, size_t tuple_len,
                            const char *insert, size_t *out_len)
{
    char **result;
    size_t total;
    size_t i;
    size_t pos;

    if (tuple == NULL || insert == NULL || out_len == NULL) {
        return NULL;
    }

    *out_len = 0U;

    if (tuple_len == 0U) {
        return NULL;
    }

    if (tuple_len > (SIZE_MAX / sizeof(char *)) / 2U) {
        return NULL;
    }

    total = tuple_len * 2U;
    result = calloc(total, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    pos = 0U;
    for (i = 0U; i < tuple_len; i++) {
        result[pos] = duplicate_string(tuple[i]);
        if (result[pos] == NULL) {
            free_string_list(result, pos);
            return NULL;
        }
        pos++;

        result[pos] = duplicate_string(insert);
        if (result[pos] == NULL) {
            free_string_list(result, pos);
            return NULL;
        }
        pos++;
    }

    *out_len = total;
    return result;
}

int main(void)
{
    const char *tuple[] = { "apple", "banana", "cherry" };
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);
    const char *insert = "FRUIT";
    char **list;
    size_t list_len = 0U;
    size_t i;

    list = tuple_to_list(tuple, tuple_len, insert, &list_len);
    if (list == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("[");
    for (i = 0U; i < list_len; i++) {
        printf("'%s'", list[i]);
        if (i + 1U < list_len) {
            printf(", ");
        }
    }
    printf("]\n");

    free_string_list(list, list_len);
    return EXIT_SUCCESS;
}