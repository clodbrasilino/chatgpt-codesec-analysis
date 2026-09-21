#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

    if (count > SIZE_MAX / sizeof(char *)) {
        free(tuple);
        return NULL;
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

        tuple->items[i] = strdup(list[i]);
        if (tuple->items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }
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