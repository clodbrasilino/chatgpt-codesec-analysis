#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *duplicate_string(const char *str) {
    if (!str) {
        return NULL;
    }

    size_t len = 0;
    size_t max_len = 4096;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    char *copy = malloc(len + 1);
    if (copy) {
        for (size_t i = 0; i < len; i++) {
            copy[i] = str[i];
        }
        copy[len] = '\0';
    }
    
    return copy;
}

char **convert_tuple_to_list(const char **tuple, size_t tuple_size, const char *add_str, size_t *out_size) {
    if (!tuple || !add_str || !out_size) {
        return NULL;
    }

    if (tuple_size > SIZE_MAX / 2) {
        return NULL;
    }

    *out_size = tuple_size * 2;
    if (*out_size == 0 || *out_size > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    char **list = malloc(*out_size * sizeof(char *));
    if (!list) {
        return NULL;
    }

    for (size_t i = 0; i < tuple_size; ++i) {
        if (!tuple[i]) {
            for (size_t j = 0; j < i * 2; ++j) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }

        list[i * 2] = duplicate_string(tuple[i]);
        if (!list[i * 2]) {
            for (size_t j = 0; j < i * 2; ++j) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }

        list[i * 2 + 1] = duplicate_string(add_str);
        if (!list[i * 2 + 1]) {
            free(list[i * 2]);
            for (size_t j = 0; j < i * 2; ++j) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
    }

    return list;
}

int main(void) {
    const char *tuple[] = {"item1", "item2", "item3"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char *add_str = "added_string";
    size_t out_size = 0;

    char **list = convert_tuple_to_list(tuple, tuple_size, add_str, &out_size);
    
    if (list) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%s\n", list[i]);
            free(list[i]);
        }
        free(list);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}