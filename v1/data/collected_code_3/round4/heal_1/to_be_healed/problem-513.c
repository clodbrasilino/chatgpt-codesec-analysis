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
    List *list = malloc(sizeof(List));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list->size = tuple->size * 2;
    list->items = malloc(sizeof(char*) * list->size);

    for (int i = 0, j = 0; i < tuple->size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*list.items + (long unsigned int)j * 8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        list->items[j++] = tuple->items[i];
        list->items[j++] = str;
    }

    return list;
}

int main() {
    Tuple tuple;
    tuple.size = 3;
    tuple.items = malloc(sizeof(char*) * tuple.size);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'tuple.items' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    tuple.items[0] = "Hello";
    tuple.items[1] = "World";
    tuple.items[2] = "!";

    char *str = "AddMe";

    List *list = convert_tuple_to_list(&tuple, str);

    for (int i = 0; i < list->size; i++) {
        printf("%s ", list->items[i]);
    }

    free(tuple.items);
    free(list->items);
    free(list);

    return 0;
}