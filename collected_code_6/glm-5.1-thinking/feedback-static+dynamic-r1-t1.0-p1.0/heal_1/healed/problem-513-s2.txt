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

    size_t suffix_len = snprintf(NULL, 0, "%s", suffix);

    for (size_t i = 0; i < len; i++) {
        if (tuple[i] == NULL) {
            for (size_t j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }

        size_t slen = snprintf(NULL, 0, "%s", tuple[i]);
        list[i * 2] = malloc(slen + 1);
        if (list[i * 2] == NULL) {
            for (size_t j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        snprintf(list[i * 2], slen + 1, "%s", tuple[i]);

        list[i * 2 + 1] = malloc(suffix_len + 1);
        if (list[i * 2 + 1] == NULL) {
            free(list[i * 2]);
            for (size_t j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        snprintf(list[i * 2 + 1], suffix_len + 1, "%s", suffix);
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