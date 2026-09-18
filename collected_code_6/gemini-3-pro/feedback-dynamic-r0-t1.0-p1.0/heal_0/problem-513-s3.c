#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t size;
} Tuple;

typedef struct {
    char **elements;
    size_t size;
} List;

void free_tuple(Tuple *tuple) {
    if (tuple && tuple->elements) {
        for (size_t i = 0; i < tuple->size; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
}

void free_list(List *list) {
    if (list && list->elements) {
        for (size_t i = 0; i < list->size; i++) {
            free(list->elements[i]);
        }
        free(list->elements);
    }
}

List* convert_tuple_to_list(const Tuple *tuple, const char *str) {
    if (!tuple || !str) {
        return NULL;
    }

    List *list = (List *)malloc(sizeof(List));
    if (!list) {
        return NULL;
    }

    list->size = tuple->size * 2;
    list->elements = (char **)malloc(list->size * sizeof(char *));
    if (!list->elements) {
        free(list);
        return NULL;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        list->elements[i * 2] = strdup(tuple->elements[i]);
        if (!list->elements[i * 2]) {
            list->size = i * 2;
            free_list(list);
            free(list);
            return NULL;
        }

        list->elements[i * 2 + 1] = strdup(str);
        if (!list->elements[i * 2 + 1]) {
            list->size = i * 2 + 1;
            free_list(list);
            free(list);
            return NULL;
        }
    }

    return list;
}

int main() {
    Tuple tuple;
    tuple.size = 3;
    tuple.elements = (char **)malloc(tuple.size * sizeof(char *));
    if (!tuple.elements) {
        return 1;
    }

    tuple.elements[0] = strdup("apple");
    tuple.elements[1] = strdup("banana");
    tuple.elements[2] = strdup("cherry");

    if (!tuple.elements[0] || !tuple.elements[1] || !tuple.elements[2]) {
        free_tuple(&tuple);
        return 1;
    }

    const char *str_to_add = "fruit";
    List *list = convert_tuple_to_list(&tuple, str_to_add);

    if (list) {
        for (size_t i = 0; i < list->size; i++) {
            printf("%s\n", list->elements[i]);
        }
        free_list(list);
        free(list);
    }

    free_tuple(&tuple);

    return 0;
}