#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    int listSize;
} Tuple;

Tuple* createTuple(char *str, int *list, int listSize) {
    Tuple *newTuple = (Tuple*)malloc(sizeof(Tuple));
    if (newTuple == NULL) {
        return NULL;
    }
    newTuple->str = (char*)malloc(strlen(str) + 1);
    if (newTuple->str == NULL) {
        free(newTuple);
        return NULL;
    }
    strcpy(newTuple->str, str);
    newTuple->list = (int*)malloc(listSize * sizeof(int));
    if (newTuple->list == NULL) {
        free(newTuple->str);
        free(newTuple);
        return NULL;
    }
    memcpy(newTuple->list, list, listSize * sizeof(int));
    newTuple->listSize = listSize;
    return newTuple;
}

void printTuple(Tuple *tuple) {
    if (tuple != NULL) {
        printf("String: %s\n", tuple->str);
        printf("List: ");
        for (int i = 0; i < tuple->listSize; i++) {
            printf("%d ", tuple->list[i]);
        }
        printf("\n");
    }
}

void freeTuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple->list);
        free(tuple);
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    Tuple *tuple = createTuple("Hello", list, 5);
    if (tuple != NULL) {
        printTuple(tuple);
        freeTuple(tuple);
    } else {
        printf("Failed to create tuple.\n");
    }
    return 0;
}