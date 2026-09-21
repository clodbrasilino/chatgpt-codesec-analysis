#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t size;
} Tuple;

static size_t safe_strlen(const char *str) {
    size_t len = 0;
    while (len < SIZE_MAX && str[len] != '\0') {
        len++;
    }
    return len;
}

Tuple string_list_to_tuple(char **list, size_t size) {
    Tuple tuple;
    tuple.size = 0;
    tuple.items = NULL;
    
    if (size == 0 || list == NULL) {
        return tuple;
    }
    
    if (size > SIZE_MAX / sizeof(char *)) {
        return tuple;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            return tuple;
        }
    }
    
    tuple.items = (char **)malloc(size * sizeof(char *));
    if (tuple.items == NULL) {
        return tuple;
    }
    
    for (size_t i = 0; i < size; i++) {
        const char *src = list[i];
        size_t len = safe_strlen(src);
        
        if (len == SIZE_MAX) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            return tuple;
        }
        
        size_t alloc_size = len + 1;
        
        if (alloc_size == 0) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            return tuple;
        }
        
        tuple.items[i] = (char *)malloc(alloc_size);
        if (tuple.items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            return tuple;
        }
        
        memcpy(tuple.items[i], src, len);
        tuple.items[i][len] = '\0';
    }
    tuple.size = size;
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