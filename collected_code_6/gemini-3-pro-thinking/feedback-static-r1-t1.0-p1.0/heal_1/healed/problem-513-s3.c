#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *duplicate_string(const char *src) {
    if (!src) {
        return NULL;
    }

    size_t len = 0;
    size_t max_len = 4096;
    while (src[len] != '\0' && len < max_len) {
        len++;
    }

    char *dest = malloc(len + 1);
    if (!dest) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        dest[i] = src[i];
    }
    dest[len] = '\0';

    return dest;
}

char **convert_tuple_to_list(const char **tuple, size_t tuple_size, const char *add_str, size_t *list_size) {
    if (!tuple || !add_str || !list_size) {
        return NULL;
    }

    if (tuple_size > SIZE_MAX / 2) {
        return NULL;
    }

    size_t new_size = tuple_size * 2;
    char **list = calloc(new_size, sizeof(char *));
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

    *list_size = new_size;
    return list;
}

int main(void) {
    const char *tuple[] = {"element1", "element2", "element3"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char *add_str = "inserted_string";
    size_t list_size = 0;

    char **list = convert_tuple_to_list(tuple, tuple_size, add_str, &list_size);
    if (!list) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list_size; ++i) {
        printf("%s\n", list[i]);
    }

    for (size_t i = 0; i < list_size; ++i) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}