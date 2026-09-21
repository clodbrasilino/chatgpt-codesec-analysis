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
    Tuple *t;
    void **items;
    
    if (element_size == 0) return NULL;
    if (initial_capacity == 0) initial_capacity = 1;
    
    if (initial_capacity > (size_t)-1 / sizeof(void *)) return NULL;
    
    t = (Tuple *)malloc(sizeof(Tuple));
    if (!t) return NULL;
    
    items = (void **)malloc(sizeof(void *) * initial_capacity);
    if (!items) {
        free(t);
        return NULL;
    }
    
    t->element_size = element_size;
    t->size = 0;
    t->capacity = initial_capacity;
    t->items = items;
    
    return t;
}

int tuple_add(Tuple *t, void *element) {
    void *item;
    
    if (!t || !element) return -1;
    if (t->element_size == 0) return -1;
    
    if (t->size >= t->capacity) {
        size_t new_capacity;
        void **new_items;
        
        if (t->capacity > (size_t)-1 / 2 / sizeof(void *)) return -1;
        new_capacity = t->capacity * 2;
        new_items = (void **)realloc(t->items, sizeof(void *) * new_capacity);
        if (!new_items) return -1;
        t->items = new_items;
        t->capacity = new_capacity;
    }
    
    item = malloc(t->element_size);
    if (!item) return -1;
    
    if (t->element_size > (size_t)-1) {
        free(item);
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(item, element, t->element_size);
    t->items[t->size++] = item;
    
    return 0;
}

void tuple_free(Tuple *t) {
    size_t i;
    
    if (!t) return;
    
    for (i = 0; i < t->size; i++) {
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
    size_t min_size;
    size_t combined_size;
    Tuple *result;
    unsigned char *buffer;
    size_t i;
    ZippedTuple *zipped;
    
    if (!t1 || !t2 || t1->element_size != t2->element_size) return NULL;
    if (t1->element_size == 0) return NULL;
    
    min_size = t1->size < t2->size ? t1->size : t2->size;
    
    if (t1->element_size > (size_t)-1 / 2) return NULL;
    combined_size = t1->element_size * 2;
    
    if (combined_size < t1->element_size) return NULL;
    
    result = tuple_create(combined_size, min_size);
    if (!result) return NULL;
    
    buffer = (unsigned char *)malloc(combined_size);
    if (!buffer) {
        tuple_free(result);
        return NULL;
    }
    
    for (i = 0; i < min_size; i++) {
        if (t1->items[i] == NULL || t2->items[i] == NULL) {
            free(buffer);
            tuple_free(result);
            return NULL;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, t1->items[i], t1->element_size);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer + t1->element_size, t2->items[i], t2->element_size);
        
        if (tuple_add(result, buffer) != 0) {
            free(buffer);
            tuple_free(result);
            return NULL;
        }
    }
    
    free(buffer);
    
    zipped = (ZippedTuple *)malloc(sizeof(ZippedTuple));
    if (!zipped) {
        tuple_free(result);
        return NULL;
    }
    
    zipped->first = t1;
    zipped->second = t2;
    
    return zipped;
}

void zipped_tuple_free(ZippedTuple *zt) {
    if (!zt) return;
    tuple_free(zt->first);
    tuple_free(zt->second);
    free(zt);
}

int main(void) {
    Tuple *t1;
    Tuple *t2;
    int values1[] = {1, 2, 3};
    int values2[] = {10, 20, 30};
    int i;
    ZippedTuple *zipped;
    
    t1 = tuple_create(sizeof(int), 3);
    t2 = tuple_create(sizeof(int), 3);
    
    if (!t1 || !t2) {
        fprintf(stderr, "Failed to create tuples\n");
        tuple_free(t1);
        tuple_free(t2);
        return EXIT_FAILURE;
    }
    
    for (i = 0; i < 3; i++) {
        if (tuple_add(t1, &values1[i]) != 0 || tuple_add(t2, &values2[i]) != 0) {
            fprintf(stderr, "Failed to add elements\n");
            tuple_free(t1);
            tuple_free(t2);
            return EXIT_FAILURE;
        }
    }
    
    zipped = zip_tuples(t1, t2);
    if (!zipped) {
        fprintf(stderr, "Failed to zip tuples\n");
        tuple_free(t1);
        tuple_free(t2);
        return EXIT_FAILURE;
    }
    
    zipped_tuple_free(zipped);
    
    return EXIT_SUCCESS;
}