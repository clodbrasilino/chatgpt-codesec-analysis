#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    int listSize;
} Tuple;

Tuple* createTuple(char *str, int *list, int listSize) {
    Tuple *newTuple = (Tuple*) malloc(sizeof(Tuple));
    newTuple->str = (char*) malloc(strlen(str) + 1);
    strcpy(newTuple->str, str);
    newTuple->list = (int*) malloc(listSize * sizeof(int));
    memcpy(newTuple->list, list, listSize * sizeof(int));
    newTuple->listSize = listSize;
    return newTuple;
}

void printTuple(Tuple *tuple) {
    printf("String: %s\n", tuple->str);
    printf("List: ");
    for(int i = 0; i < tuple->listSize; i++) {
        printf("%d ", tuple->list[i]);
    }
    printf("\n");
}

void freeTuple(Tuple *tuple) {
    free(tuple->str);
    free(tuple->list);
    free(tuple);
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    Tuple *tuple = createTuple("Hello", list, 5);
    printTuple(tuple);
    freeTuple(tuple);
    return 0;
}