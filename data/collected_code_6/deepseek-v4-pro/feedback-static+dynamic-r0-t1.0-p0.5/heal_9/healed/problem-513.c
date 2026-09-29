#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char **tuple_to_list(const char *tuple[], int tuple_size, const char *str, int *list_size) {
    if (tuple == NULL || str == NULL || list_size == NULL || tuple_size <= 0) {
        if (list_size != NULL) {
            *list_size = 0;
        }
        return NULL;
    }

    size_t str_len = strnlen(str, SIZE_MAX);
    if (str_len == SIZE_MAX) {
        *list_size = 0;
        return NULL;
    }

    char **list = (char **)malloc((size_t)tuple_size * sizeof(char *));
    if (list == NULL) {
        *list_size = 0;
        return NULL;
    }

    for (int i = 0; i < tuple_size; i++) {
        if (tuple[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            *list_size = 0;
            return NULL;
        }

        size_t tuple_len = strnlen(tuple[i], SIZE_MAX);
        if (tuple_len == SIZE_MAX) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            *list_size = 0;
            return NULL;
        }

        if (tuple_len > SIZE_MAX - str_len - 1) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            *list_size = 0;
            return NULL;
        }

        size_t total_len = tuple_len + str_len + 1;

        list[i] = (char *)malloc(total_len);
        if (list[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            *list_size = 0;
            return NULL;
        }

        if (tuple_len > 0) {
            memcpy(list[i], tuple[i], tuple_len);
        }
        if (str_len > 0) {
            memcpy(list[i] + tuple_len, str, str_len);
        }
        list[i][tuple_len + str_len] = '\0';
    }

    *list_size = tuple_size;
    return list;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    int tuple_size = (int)(sizeof(tuple) / sizeof(tuple[0]));
    int list_size = 0;
    char **list = tuple_to_list(tuple, tuple_size, "_fruit", &list_size);

    if (list == NULL) {
        fprintf(stderr, "Error: Failed to convert tuple to list\n");
        return 1;
    }

    for (int i = 0; i < list_size; i++) {
        printf("%s\n", list[i]);
        free(list[i]);
    }
    free(list);

    return 0;
}