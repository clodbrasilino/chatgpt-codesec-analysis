#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int size;
} Tuple;

Tuple* create_tuple(char **list, int size) {
    Tuple *tuple = (Tuple*) malloc(sizeof(Tuple));

    if(tuple == NULL)
        return NULL;

    tuple->items = (char**) malloc(size * sizeof(char*));
    if (tuple->items == NULL){
        free(tuple);
        return NULL;
    }

    tuple->size = size;

    for (int i = 0; i < size; i++) {
        tuple->items[i] = (char*) malloc((strlen(list[i]) + 1) * sizeof(char));
        
        if(tuple->items[i] == NULL){
            for(int j = 0; j < i; j++)
                free(tuple->items[j]);

            free(tuple->items);
            free(tuple);
            return NULL;
        }

        strcpy(tuple->items[i], list[i]);
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    for (int i = 0; i < tuple->size; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    free(tuple);
}

int main() {
    char *list[] = {"Hello", "World", "This", "Is", "C"};
    int size = sizeof(list) / sizeof(list[0]);

    Tuple *tuple = create_tuple(list, size);

    if(tuple == NULL)
        return 1;

    for (int i = 0; i < tuple->size; i++) {
        printf("%s ", tuple->items[i]);
    }

    free_tuple(tuple);

    return 0;
}