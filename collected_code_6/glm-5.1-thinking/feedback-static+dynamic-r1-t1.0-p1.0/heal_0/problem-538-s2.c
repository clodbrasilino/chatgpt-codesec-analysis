#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringTuple;

StringTuple *string_list_to_tuple(char **list, size_t count) {
    if (list == NULL) {
        return NULL;
    }

    StringTuple *tuple = malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->count = count;
    if (count == 0) {
        tuple->items = NULL;
        return tuple;
    }

    tuple->items = malloc(count * sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }

        size_t len = strlen(list[i]);
        tuple->items[i] = malloc(len + 1);
        if (tuple->items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }
        memcpy(tuple->items[i], list[i], len + 1);
    }

    return tuple;
}

void free_string_tuple(StringTuple *tuple) {
    if (tuple == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    free(tuple);
}

int main(void) {
    char *list[] = {"apple", "banana", "cherry"};
    size_t count = sizeof(list) / sizeof(list[0]);

    StringTuple *tuple = string_list_to_tuple(list, count);
    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        printf("%s\n", tuple->items[i]);
    }

    free_string_tuple(tuple);

    return EXIT_SUCCESS;
}