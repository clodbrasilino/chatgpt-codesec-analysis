#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **items;
    size_t size;
    size_t capacity;
    size_t element_size;
} Tuple;

Tuple *tuple_create(size_t element_size, size_t initial_capacity) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (!t) return NULL;
    
    t->element_size = element_size;
    t->size = 0;
    t->capacity = initial_capacity > 0 ? initial_capacity : 1;
    t->items = (void **)malloc(sizeof(void *) * t->capacity);
    if (!t->items) {
        free(t);
        return NULL;
    }
    
    return t;
}

int tuple_add(Tuple *t, void *element) {
    if (!t || !element) return -1;
    
    if (t->size >= t->capacity) {
        size_t new_capacity = t->capacity * 2;
        void **new_items = (void **)realloc(t->items, sizeof(void *) * new_capacity);
        if (!new_items) return -1;
        t->items = new_items;
        t->capacity = new_capacity;
    }
    
    void *item = malloc(t->element_size);
    if (!item) return -1;
    
    memcpy(item, element, t->element_size);
    t->items[t->size++] = item;
    
    return 0;
}

void tuple_free(Tuple *t) {
    if (!t) return;
    
    for (size_t i = 0; i < t->size; i++) {
        free(t->items[i]);
    }
    free(t->items);
    free(t);
}

typedef struct {
    Tuple *first;
    Tuple *second;
} ZippedTuple;

ZippedTuple *zip_tuples(Tuple *t1, Tuple *t2) {
    if (!t1 || !t2 || t1->element_size != t2->element_size) return NULL;
    
    size_t min_size = t1->size < t2->size ? t1->size : t2->size;
    
    Tuple *result = tuple_create(t1->element_size * 2, min_size);
    if (!result) return NULL;
    
    unsigned char *buffer = (unsigned char *)malloc(t1->element_size * 2);
    if (!buffer) {
        tuple_free(result);
        return NULL;
    }
    
    for (size_t i = 0; i < min_size; i++) {
        memcpy(buffer, t1->items[i], t1->element_size);
        memcpy(buffer + t1->element_size, t2->items[i], t2->element_size);
        if (tuple_add(result, buffer) != 0) {
            free(buffer);
            tuple_free(result);
            return NULL;
        }
    }
    
    free(buffer);
    
    ZippedTuple *zipped = (ZippedTuple *)malloc(sizeof(ZippedTuple));
    if (!zipped) {
        tuple_free(result);
        return NULL;
    }
    
    zipped->first = t1;
    zipped->second = t2;
    
    return zipped;
}

int main(void) {
    Tuple *t1 = tuple_create(sizeof(int), 3);
    Tuple *t2 = tuple_create(sizeof(int), 3);
    
    if (!t1 || !t2) {
        fprintf(stderr, "Failed to create tuples\n");
        tuple_free(t1);
        tuple_free(t2);
        return EXIT_FAILURE;
    }
    
    int values1[] = {1, 2, 3};
    int values2[] = {10, 20, 30};
    
    for (int i = 0; i < 3; i++) {
        if (tuple_add(t1, &values1[i]) != 0 || tuple_add(t2, &values2[i]) != 0) {
            fprintf(stderr, "Failed to add elements\n");
            tuple_free(t1);
            tuple_free(t2);
            return EXIT_FAILURE;
        }
    }
    
    ZippedTuple *zipped = zip_tuples(t1, t2);
    if (!zipped) {
        fprintf(stderr, "Failed to zip tuples\n");
        tuple_free(t1);
        tuple_free(t2);
        return EXIT_FAILURE;
    }
    
    tuple_free(t1);
    tuple_free(t2);
    free(zipped);
    
    return EXIT_SUCCESS;
}