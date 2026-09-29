#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char **convert_tuple_to_list(const char *const *tuple, size_t tuple_len, const char *suffix, size_t *list_len) {
    if (tuple == NULL || suffix == NULL || list_len == NULL) {
        return NULL;
    }

    size_t out_len = tuple_len * 2;
    char **list = malloc(out_len * sizeof(char *));
    if (list == NULL) {
        return NULL;
    }

    size_t suffix_len = strnlen(suffix, SIZE_MAX);

    for (size_t i = 0; i < tuple_len; ++i) {
        size_t elem_idx = i * 2;
        size_t suff_idx = i * 2 + 1;

        size_t elem_len = (tuple[i] != NULL) ? strnlen(tuple[i], SIZE_MAX) : 0;

        list[elem_idx] = malloc(elem_len + 1);
        if (list[elem_idx] == NULL) {
            for (size_t j = 0; j < elem_idx; ++j) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        if (tuple[i] != NULL) {
            snprintf(list[elem_idx], elem_len + 1, "%s", tuple[i]);
        } else {
            list[elem_idx][0] = '\0';
        }

        list[suff_idx] = malloc(suffix_len + 1);
        if (list[suff_idx] == NULL) {
            for (size_t j = 0; j <= elem_idx; ++j) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        snprintf(list[suff_idx], suffix_len + 1, "%s", suffix);
    }

    *list_len = out_len;
    return list;
}

void free_list(char **list, size_t len) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < len; ++i) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *tuple[] = {"10", "20", "30", "40"};
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);
    const char *suffix = "x";
    size_t list_len = 0;

    char **list = convert_tuple_to_list(tuple, tuple_len, suffix, &list_len);

    if (list != NULL) {
        printf("[");
        for (size_t i = 0; i < list_len; ++i) {
            printf("'%s'", list[i]);
            if (i < list_len - 1) {
                printf(", ");
            }
        }
        printf("]\n");

        free_list(list, list_len);
    }

    return 0;
}