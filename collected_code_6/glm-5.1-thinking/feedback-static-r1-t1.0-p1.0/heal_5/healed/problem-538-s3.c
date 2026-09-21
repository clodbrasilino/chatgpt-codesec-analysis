#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple string_list_to_tuple(char **list) {
    Tuple tuple = {NULL, 0};
    size_t len = 0;

    if (list == NULL) {
        return tuple;
    }

    while (list[len] != NULL) {
        len++;
    }

    if (len == 0) {
        return tuple;
    }

    tuple.items = malloc((len + 1) * sizeof(char *));
    if (tuple.items == NULL) {
        return tuple;
    }

    for (size_t i = 0; i < len; i++) {
        size_t str_len = strnlen(list[i], MAX_STR_LEN);
        
        tuple.items[i] = malloc(str_len + 1);
        if (tuple.items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.count = 0;
            return tuple;
        }

        snprintf(tuple.items[i], str_len + 1, "%s", list[i]);
    }

    tuple.items[len] = NULL;
    tuple.count = len;

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
}

int main(void) {
    char *list[] = {"apple", "banana", "cherry", NULL};
    Tuple t = string_list_to_tuple(list);

    if (t.items != NULL) {
        for (size_t i = 0; i < t.count; i++) {
            printf("%s\n", t.items[i]);
        }
        free_tuple(&t);
    }

    Tuple null_test = string_list_to_tuple(NULL);
    if (null_test.items == NULL && null_test.count == 0) {
        printf("Handled NULL input correctly.\n");
    }

    return 0;
}