#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    char **items;
    size_t length;
} Tuple;

static char *duplicate_string(const char *str) {
    size_t length;
    char *copy;

    if (str == NULL) {
        return NULL;
    }

    length = strlen(str) + 1;
    copy = malloc(length);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, str, length);
    return copy;
}

Tuple *string_list_to_tuple(char **list, size_t count) {
    Tuple *tuple;

    if (list == NULL && count > 0) {
        return NULL;
    }

    tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->length = 0;

    if (count > 0) {
        tuple->items = calloc(count, sizeof(char *));
        if (tuple->items == NULL) {
            free(tuple);
            return NULL;
        }
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

        tuple->items[i] = duplicate_string(list[i]);
        if (tuple->items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }
    }

    tuple->length = count;
    return tuple;
}

void tuple_free(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->length; i++) {
            free(tuple->items[i]);
        }
    }

    free(tuple->items);
    free(tuple);
}

int main(void) {
    char *list[] = {"red", "green", "blue"};
    size_t count = sizeof(list) / sizeof(list[0]);
    Tuple *tuple;

    tuple = string_list_to_tuple(list, count);
    if (tuple == NULL) {
        return 1;
    }

    for (size_t i = 0; i < tuple->length; i++) {
        printf("%s\n", tuple->items[i]);
    }

    tuple_free(tuple);
    return 0;
}