#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *str_dup(const char *src) {
    if (src == NULL) {
        return NULL;
    }
    size_t len = strnlen(src, SIZE_MAX) + 1;
    char *dst = malloc(len);
    if (dst) {
        memcpy(dst, src, len);
    }
    return dst;
}

char **convert_tuple_to_list(const char **tuple, size_t tuple_len, const char *suffix, size_t *list_len) {
    if (tuple == NULL || suffix == NULL || list_len == NULL) {
        if (list_len) *list_len = 0;
        return NULL;
    }
    
    if (tuple_len == 0) {
        *list_len = 0;
        return NULL;
    }

    if (tuple_len > SIZE_MAX / 2) {
        *list_len = 0;
        return NULL;
    }

    size_t len = tuple_len * 2;

    if (len > SIZE_MAX / sizeof(char *)) {
        *list_len = 0;
        return NULL;
    }

    char **list = malloc(len * sizeof(char *));
    if (!list) {
        *list_len = 0;
        return NULL;
    }

    for (size_t i = 0; i < tuple_len; i++) {
        if (tuple[i] == NULL) {
            for (size_t j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            *list_len = 0;
            return NULL;
        }

        list[i * 2] = str_dup(tuple[i]);
        if (!list[i * 2]) {
            for (size_t j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            *list_len = 0;
            return NULL;
        }

        list[i * 2 + 1] = str_dup(suffix);
        if (!list[i * 2 + 1]) {
            free(list[i * 2]);
            for (size_t j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            *list_len = 0;
            return NULL;
        }
    }

    *list_len = len;
    return list;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);
    const char *suffix = "extra";
    size_t list_len = 0;

    char **list = convert_tuple_to_list(tuple, tuple_len, suffix, &list_len);

    if (list) {
        for (size_t i = 0; i < list_len; i++) {
            printf("%s\n", list[i]);
            free(list[i]);
        }
        free(list);
    }

    return 0;
}