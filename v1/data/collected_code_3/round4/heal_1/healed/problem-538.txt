#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int size;
} Tuple;

Tuple stringListToTuple(char **list, int size) {
    Tuple tuple;
    tuple.items = (char**)malloc(sizeof(char*) * size);
    if (tuple.items == NULL) {
        tuple.size = 0;
        return tuple;
    }
    tuple.size = size;
    for(int i = 0; i < size; i++) {
        tuple.items[i] = (char*)malloc(sizeof(char) * (strlen(list[i]) + 1));
        if (tuple.items[i] == NULL) {
            for(--i; i >= 0; --i){
                free(tuple.items[i]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }
        strcpy(tuple.items[i], list[i]);
    }
    return tuple;
}

void freeTuple(Tuple tuple) {
    for(int i = 0; i < tuple.size; i++) {
        free(tuple.items[i]);
    }
    free(tuple.items);
}

int main() {
    char *list[] = {"Hello", "World", "This", "Is", "C"};
    int size = sizeof(list) / sizeof(list[0]);

    Tuple tuple = stringListToTuple(list, size);
    if(tuple.items == NULL){
        printf("Failed to allocate memory\n");
        return -1;
    }

    for(int i = 0; i < tuple.size; i++) {
        printf("%s ", tuple.items[i]);
    }

    freeTuple(tuple);

    return 0;
}