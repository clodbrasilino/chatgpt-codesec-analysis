#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t size;
} Tuple;

Tuple string_list_to_tuple(char **list, size_t count) {
    Tuple tuple;
    tuple.size = count;
    tuple.items = NULL;
    
    if (count == 0) {
        tuple.size = 0;
        return tuple;
    }
    
    if (count > SIZE_MAX / sizeof(char *)) {
        tuple.size = 0;
        return tuple;
    }
    
    tuple.items = (char **)malloc(count * sizeof(char *));
    if (tuple.items == NULL) {
        tuple.size = 0;
        return tuple;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (list[i] == NULL) {
            tuple.items[i] = NULL;
            continue;
        }
        
        size_t len = strnlen(list[i], SIZE_MAX);
        
        if (len >= SIZE_MAX) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }
        
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
        
        if (len > 0) {
            memcpy(tuple.items[i], list[i], len);
        }
        tuple.items[i][len] = '\0';
    }
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
}

int main(void) {
    char *list[] = {"hello", "world", "tuple", "example"};
    size_t count = sizeof(list) / sizeof(list[0]);
    
    Tuple tuple = string_list_to_tuple(list, count);
    if (tuple.items == NULL && count > 0) {
        fprintf(stderr, "Failed to create tuple\n");
        return 1;
    }
    
    printf("Tuple contents:\n");
    for (size_t i = 0; i < tuple.size; i++) {
        if (tuple.items[i] != NULL) {
            printf("  [%zu] %s\n", i, tuple.items[i]);
        } else {
            printf("  [%zu] (null)\n", i);
        }
    }
    
    free_tuple(&tuple);
    return 0;
}