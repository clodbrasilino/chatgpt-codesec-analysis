#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t length;
} Tuple;

static char *safe_strdup(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t max_len = 0;
    const char *p = str;
    while (max_len < SIZE_MAX && *p != '\0') {
        max_len++;
        p++;
    }
    if (max_len == SIZE_MAX) {
        return NULL;
    }
    char *copy = (char *)malloc(max_len + 1);
    if (copy == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < max_len; i++) {
        copy[i] = str[i];
    }
    copy[max_len] = '\0';
    return copy;
}

Tuple string_list_to_tuple(char **list, size_t size) {
    Tuple tuple;
    tuple.length = size;
    tuple.items = NULL;

    if (size == 0) {
        return tuple;
    }

    tuple.items = (char **)malloc(size * sizeof(char *));
    if (tuple.items == NULL) {
        tuple.length = 0;
        return tuple;
    }

    for (size_t i = 0; i < size; i++) {
        tuple.items[i] = NULL;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.length = 0;
            return tuple;
        }

        tuple.items[i] = safe_strdup(list[i]);
        if (tuple.items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.length = 0;
            return tuple;
        }
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->length; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->length = 0;
}

int main(void) {
    char *str_list[] = {"hello", "world", "tuple", "example"};
    size_t size = sizeof(str_list) / sizeof(str_list[0]);

    Tuple tuple = string_list_to_tuple(str_list, size);
    if (tuple.items == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("Tuple contents:\n");
    for (size_t i = 0; i < tuple.length; i++) {
        printf("  [%zu] %s\n", i, tuple.items[i]);
    }

    free_tuple(&tuple);
    return EXIT_SUCCESS;
}