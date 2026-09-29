#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    int size;
} Tuple;

Tuple* convertToTuple(char **list, int size) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    tuple->data = (char**)malloc(sizeof(char*) * size);
    tuple->size = size;
    for(int i = 0; i < size; i++) {
        tuple->data[i] = (char*)malloc(sizeof(char) * (strlen(list[i]) + 1));
        strcpy(tuple->data[i], list[i]);
    }
    return tuple;
}

void freeTuple(Tuple *tuple) {
    for(int i = 0; i < tuple->size; i++) {
        free(tuple->data[i]);
    }
    free(tuple->data);
    free(tuple);
}

int main() {
    char *list[] = {"Hello", "World", "C", "Programming"};
    int size = sizeof(list) / sizeof(list[0]);
    Tuple *tuple = convertToTuple(list, size);
    for(int i = 0; i < tuple->size; i++) {
        printf("%s ", tuple->data[i]);
    }
    printf("\n");
    freeTuple(tuple);
    return 0;
}