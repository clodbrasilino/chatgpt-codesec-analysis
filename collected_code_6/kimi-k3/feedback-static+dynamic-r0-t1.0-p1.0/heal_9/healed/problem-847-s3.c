#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    void **items;
    size_t size;
    size_t capacity;
} List;

typedef struct {
    List *list;
} SingletonTuple;

List *list_create(size_t capacity) {
    if (capacity == 0 || capacity > SIZE_MAX / sizeof(void *)) {
        return NULL;
    }
    
    List *list = malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    
    list->items = calloc(capacity, sizeof(void *));
    if (list->items == NULL) {
        free(list);
        return NULL;
    }
    
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void list_destroy(List *list) {
    if (list != NULL) {
        free(list->items);
        free(list);
    }
}

SingletonTuple *singleton_tuple_create(List *list) {
    if (list == NULL) {
        return NULL;
    }
    
    SingletonTuple *tuple = malloc(sizeof(SingletonTuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->list = list;
    return tuple;
}

void singleton_tuple_destroy(SingletonTuple *tuple) {
    if (tuple != NULL) {
        free(tuple);
    }
}

List *copy_list_from_singleton_tuple(const SingletonTuple *tuple) {
    if (tuple == NULL || tuple->list == NULL) {
        return NULL;
    }
    
    const List *source = tuple->list;
    
    if (source->size > source->capacity) {
        return NULL;
    }
    
    if (source->capacity == 0 || source->capacity > SIZE_MAX / sizeof(void *)) {
        return NULL;
    }
    
    if (source->size > 0 && source->items == NULL) {
        return NULL;
    }
    
    List *copy = list_create(source->capacity);
    if (copy == NULL) {
        return NULL;
    }
    
    if (source->size > 0) {
        size_t copy_size = source->size * sizeof(void *);
        size_t dest_capacity_bytes = copy->capacity * sizeof(void *);
        
        if (copy_size > dest_capacity_bytes) {
            list_destroy(copy);
            return NULL;
        }
        
        if (copy->items == NULL || source->items == NULL) {
            list_destroy(copy);
            return NULL;
        }
        
        memcpy(copy->items, source->items, copy_size);
        copy->size = source->size;
    }
    
    return copy;
}

int main(void) {
    List *original = list_create(10);
    if (original == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return EXIT_FAILURE;
    }
    
    int a = 1, b = 2, c = 3;
    original->items[0] = &a;
    original->items[1] = &b;
    original->items[2] = &c;
    original->size = 3;
    
    SingletonTuple *tuple = singleton_tuple_create(original);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create singleton tuple\n");
        list_destroy(original);
        return EXIT_FAILURE;
    }
    
    List *copied = copy_list_from_singleton_tuple(tuple);
    if (copied == NULL) {
        fprintf(stderr, "Failed to copy list\n");
        singleton_tuple_destroy(tuple);
        list_destroy(original);
        return EXIT_FAILURE;
    }
    
    printf("Original size: %zu\n", original->size);
    printf("Copied size: %zu\n", copied->size);
    printf("First element: %d\n", *(int *)copied->items[0]);
    
    list_destroy(copied);
    singleton_tuple_destroy(tuple);
    list_destroy(original);
    
    return EXIT_SUCCESS;
}