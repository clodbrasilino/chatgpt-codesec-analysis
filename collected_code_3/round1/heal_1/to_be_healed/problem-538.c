#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int size;
} Tuple;

Tuple* stringListToTuple(char **list, int size) {
    Tuple *tuple = malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'tuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    tuple->items = malloc(sizeof(char*) * size);
    tuple->size = size;
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*tuple.items + (long unsigned int)i * 8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuple->items[i] = malloc(sizeof(char) * (strlen(list[i]) + 1));
        strcpy(tuple->items[i], list[i]);
    }
    return tuple;
}

void freeTuple(Tuple *tuple) {
    for(int i = 0; i < tuple->size; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    free(tuple);
}

int main() {
    char *list[] = {"item1", "item2", "item3"};
    int size = sizeof(list) / sizeof(list[0]);
    Tuple *tuple = stringListToTuple(list, size);
    for(int i = 0; i < tuple->size; i++) {
        printf("%s\n", tuple->items[i]);
    }
    freeTuple(tuple);
    return 0;
}