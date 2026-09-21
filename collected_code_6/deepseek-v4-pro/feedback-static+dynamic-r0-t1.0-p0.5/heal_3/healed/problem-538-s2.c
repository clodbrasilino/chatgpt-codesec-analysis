#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t size;
} Tuple;

Tuple string_list_to_tuple(char **list, size_t size) {
    Tuple tuple;
    tuple.size = size;
    
    if (size == 0 || list == NULL) {
        tuple.items = NULL;
        tuple.size = 0;
        return tuple;
    }
    
    tuple.items = (char **)malloc(size * sizeof(char *));
    if (tuple.items == NULL) {
        tuple.size = 0;
        return tuple;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }
        
        size_t len = strlen(list[i]);
        tuple.items[i] = (char *)malloc(len + 1);
        if (tuple.items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }
        
        memcpy(tuple.items[i], list[i], len + 1);
    }
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        free(tuple->items[i]);
        tuple->items[i] = NULL;
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
}

int main(void) {
    char *list[] = {"hello", "world", "tuple", "example"};
    size_t size = sizeof(list) / sizeof(list[0]);
    
    Tuple tuple = string_list_to_tuple(list, size);
    if (tuple.items == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return 1;
    }
    
    for (size_t i = 0; i < tuple.size; i++) {
        printf("%s\n", tuple.items[i]);
    }
    
    free_tuple(&tuple);
    return 0;
}