#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t length;
} Tuple;

Tuple string_list_to_tuple(char **list, size_t size) {
    Tuple tuple;
    tuple.length = 0;
    tuple.items = NULL;

    if (list == NULL || size == 0) {
        return tuple;
    }

    tuple.items = (char **)calloc(size, sizeof(char *));
    if (tuple.items == NULL) {
        return tuple;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            tuple.items[i] = NULL;
            tuple.length++;
            continue;
        }

        size_t len = strnlen(list[i], size * 64);
        size_t alloc_size = len + 1;

        tuple.items[i] = (char *)malloc(alloc_size);
        if (tuple.items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.length = 0;
            return tuple;
        }

        if (len > 0) {
            memcpy(tuple.items[i], list[i], alloc_size);
        }
        tuple.items[i][len] = '\0';
        tuple.length++;
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
        if (tuple.items[i] != NULL) {
            printf("  [%zu] %s\n", i, tuple.items[i]);
        } else {
            printf("  [%zu] (null)\n", i);
        }
    }

    free_tuple(&tuple);
    return EXIT_SUCCESS;
}