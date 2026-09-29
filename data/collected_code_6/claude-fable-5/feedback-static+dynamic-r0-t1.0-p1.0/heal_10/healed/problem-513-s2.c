#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096U
#define INT_BUFFER_LEN 32U

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }

    copy = malloc(len + 1U);
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

static int int_to_string(int value, char *buffer, size_t buffer_size)
{
    int written;

    if (buffer == NULL || buffer_size == 0U) {
        return -1;
    }

    written = snprintf(buffer, buffer_size, "%d", value);
    if (written < 0 || (size_t)written >= buffer_size) {
        return -1;
    }

    buffer[buffer_size - 1U] = '\0';
    return 0;
}

static char **tuple_to_list_with_string(const int *tuple, size_t tuple_len,
                                        const char *insert, size_t *out_len)
{
    char **result;
    size_t total;
    size_t i;
    size_t idx;

    if (tuple == NULL || insert == NULL || out_len == NULL || tuple_len == 0U) {
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

    idx = 0U;
    for (i = 0U; i < tuple_len; i++) {
        char buffer[INT_BUFFER_LEN] = {0};

        if (int_to_string(tuple[i], buffer, sizeof(buffer)) != 0) {
            free_string_list(result, idx);
            return NULL;
        }

        result[idx] = duplicate_string(buffer);
        if (result[idx] == NULL) {
            free_string_list(result, idx);
            return NULL;
        }
        idx++;

        result[idx] = duplicate_string(insert);
        if (result[idx] == NULL) {
            free_string_list(result, idx);
            return NULL;
        }
        idx++;
    }

    *out_len = total;
    return result;
}

int main(void)
{
    const int tuple[] = {5, 6, 7, 4, 9};
    const size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);
    const char *insert = "FDF";
    char **list;
    size_t list_len;
    size_t i;

    list_len = 0U;
    list = tuple_to_list_with_string(tuple, tuple_len, insert, &list_len);
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