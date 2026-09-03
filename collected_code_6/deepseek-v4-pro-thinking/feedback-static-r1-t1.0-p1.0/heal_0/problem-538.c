#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t length;
} StringTuple;

void free_string_tuple(StringTuple *tuple) {
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->length; ++i) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->length = 0;
}

StringTuple string_list_to_tuple(char **list, size_t count) {
    StringTuple tuple = { NULL, 0 };
    if (count == 0 || list == NULL) {
        return tuple;
    }
    tuple.items = malloc(count * sizeof(char *));
    if (tuple.items == NULL) {
        return tuple;
    }
    tuple.length = count;
    for (size_t i = 0; i < count; ++i) {
        if (list[i] == NULL) {
            tuple.length = i;
            free_string_tuple(&tuple);
            return (StringTuple){ NULL, 0 };
        }
        size_t len = strlen(list[i]);
        tuple.items[i] = malloc(len + 1);
        if (tuple.items[i] == NULL) {
            tuple.length = i;
            free_string_tuple(&tuple);
            return (StringTuple){ NULL, 0 };
        }
        memcpy(tuple.items[i], list[i], len + 1);
    }
    return tuple;
}

int main(void) {
    char *list[] = { "hello", "world", "example" };
    size_t count = sizeof(list) / sizeof(list[0]);
    StringTuple tuple = string_list_to_tuple(list, count);
    if (tuple.items == NULL && tuple.length == 0 && count > 0) {
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < tuple.length; ++i) {
        printf("%s\n", tuple.items[i]);
    }
    free_string_tuple(&tuple);
    return EXIT_SUCCESS;
}