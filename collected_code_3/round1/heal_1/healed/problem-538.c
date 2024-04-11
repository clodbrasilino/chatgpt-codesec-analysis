#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int size;
} Tuple;

Tuple* stringListToTuple(char **list, int size) {
    Tuple *tuple = malloc(sizeof(Tuple));
    if(tuple == NULL) {
        return NULL;
    }

    tuple->items = malloc(sizeof(char*) * size);
    if(tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = size;
    for(int i = 0; i < size; i++) {
        tuple->items[i] = malloc(sizeof(char) * (strlen(list[i]) + 1));
        if(tuple->items[i] == NULL) {
            for(int j = 0; j < i; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }
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
    if(tuple == NULL) {
        return 1;
    }
    for(int i = 0; i < tuple->size; i++) {
        printf("%s\n", tuple->items[i]);
    }
    freeTuple(tuple);
    return 0;
}