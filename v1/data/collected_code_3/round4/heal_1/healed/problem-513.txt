#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int size;
} List;

typedef struct {
    char **items;
    int size;
} Tuple;

List* convert_tuple_to_list(Tuple *tuple, char *str) {
    if (!tuple || !str) return NULL;

    List *list = (List*)malloc(sizeof(List));
    if (!list) return NULL;

    list->size = tuple->size * 2;
    list->items = (char**)malloc(sizeof(char*) * list->size);
    if (!list->items) {
        free(list);
        return NULL;
    }

    for (int i = 0, j = 0; i < tuple->size; i++) {
        list->items[j++] = tuple->items[i];
        list->items[j++] = str;
    }

    return list;
}

int main() {
    Tuple tuple;
    tuple.size = 3;
    tuple.items = (char**)malloc(sizeof(char*) * tuple.size);
    if (!tuple.items) return 1;

    tuple.items[0] = "Hello";
    tuple.items[1] = "World";
    tuple.items[2] = "!";

    char *str = "AddMe";

    List *list = convert_tuple_to_list(&tuple, str);
    if (!list) {
        free(tuple.items);
        return 1;
    }

    for (int i = 0; i < list->size; i++) {
        printf("%s ", list->items[i]);
    }

    free(tuple.items);
    free(list->items);
    free(list);

    return 0;
}