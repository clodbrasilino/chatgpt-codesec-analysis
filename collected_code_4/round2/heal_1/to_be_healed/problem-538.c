#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int size;
} Tuple;

Tuple* stringListToTuple(char **stringList, int size) {
    if (stringList == NULL || size < 0) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if(tuple == NULL){
        return NULL;
    }

    tuple->items = malloc(sizeof(char *) * size);

    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    for(int i = 0; i < size; i++) {
        tuple->items[i] = malloc(strlen(stringList[i]) + 1);
        if(tuple->items[i] == NULL){
            for(int j = 0; j<i; j++){
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }

        strcpy(tuple->items[i], stringList[i]);
    }

    tuple->size = size;

    return tuple;
}

void freeTuple(Tuple *tuple) {
    if (tuple == NULL)
        return;

    for(int i = 0; i < tuple->size; i++) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    free(tuple);
}

int main() {
    char *stringList[] = {"Hello", "world", "This", "is", "a", "test"};
    int size = sizeof(stringList) / sizeof(stringList[0]);

    Tuple *tuple = stringListToTuple(stringList, size);

    /* Possible weaknesses found:
     *  dereference of NULL 'tuple' [CWE-476] [-Wanalyzer-null-dereference]
     */
    for(int i = 0; i < tuple->size; i++) {
        printf("%s ", tuple->items[i]);
    }

    freeTuple(tuple);

    return 0;
}