#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **convert_tuple_to_list(const char **tuple, size_t len, const char *suffix, size_t *out_len) {
    if (tuple == NULL || suffix == NULL || out_len == NULL) {
        return NULL;
    }

    *out_len = len * 2;
    if (len == 0) {
        return NULL;
    }

    char **list = malloc(*out_len * sizeof(char *));
    if (list == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (tuple[i] == NULL) {
            for (size_t j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }

        list[i * 2] = malloc(strlen(tuple[i]) + 1);
        if (list[i * 2] == NULL) {
            for (size_t j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        strcpy(list[i * 2], tuple[i]);

        list[i * 2 + 1] = malloc(strlen(suffix) + 1);
        if (list[i * 2 + 1] == NULL) {
            free(list[i * 2]);
            for (size_t j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        strcpy(list[i * 2 + 1], suffix);
    }

    return list;
}

void free_list(char **list, size_t len) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < len; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    const char *suffix = "fruit";
    size_t out_len = 0;

    char **list = convert_tuple_to_list(tuple, len, suffix, &out_len);

    if (list != NULL) {
        for (size_t i = 0; i < out_len; i++) {
            printf("%s\n", list[i]);
        }
        free_list(list, out_len);
    }

    return 0;
}