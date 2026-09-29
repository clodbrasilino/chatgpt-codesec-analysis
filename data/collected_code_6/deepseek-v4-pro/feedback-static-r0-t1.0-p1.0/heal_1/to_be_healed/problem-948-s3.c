#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct {
    void **items;
    size_t size;
} Tuple;

Tuple create_tuple(size_t count, ...) {
    Tuple t;
    t.size = count;
    t.items = (void**)malloc(count * sizeof(void*));
    if (t.items == NULL) {
        t.size = 0;
        return t;
    }
    
    va_list args;
    va_start(args, count);
    for (size_t i = 0; i < count; i++) {
        t.items[i] = va_arg(args, void*);
    }
    va_end(args);
    
    return t;
}

void *tuple_get(const Tuple *tuple, size_t index) {
    if (tuple == NULL || tuple->items == NULL) {
        return NULL;
    }
    if (index >= tuple->size) {
        return NULL;
    }
    return tuple->items[index];
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        free(tuple->items);
        tuple->items = NULL;
    }
    tuple->size = 0;
}

int main(void) {
    int a = 10, b = 20, c = 30;
    char *str = "hello";
    
    Tuple t = create_tuple(4, &a, &b, &c, str);
    
    if (t.items == NULL) {
        fprintf(stderr, "Failed to allocate tuple\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  Variable 'first' can be declared as pointer to const [constVariablePointer]
     */
    int *first = (int*)tuple_get(&t, 0);
    /* Possible weaknesses found:
     *  Variable 'second' can be declared as pointer to const [constVariablePointer]
     */
    int *second = (int*)tuple_get(&t, 1);
    /* Possible weaknesses found:
     *  Variable 'third' can be declared as pointer to const [constVariablePointer]
     */
    int *third = (int*)tuple_get(&t, 2);
    char *fourth = (char*)tuple_get(&t, 3);
    /* Possible weaknesses found:
     *  Variable 'out_of_bounds' can be declared as pointer to const [constVariablePointer]
     */
    void *out_of_bounds = tuple_get(&t, 10);
    /* Possible weaknesses found:
     *  Variable 'null_tuple' can be declared as pointer to const [constVariablePointer]
     *  Assignment 'null_tuple=tuple_get(NULL,0)', assigned value is 0
     *  Calling function 'tuple_get' returns 0
     */
    void *null_tuple = tuple_get(NULL, 0);
    
    if (first) printf("First: %d\n", *first);
    if (second) printf("Second: %d\n", *second);
    if (third) printf("Third: %d\n", *third);
    if (fourth) printf("Fourth: %s\n", fourth);
    
    if (out_of_bounds == NULL) {
        printf("Out of bounds returns NULL\n");
    }
    
    /* Possible weaknesses found:
     *  Condition 'null_tuple==NULL' is always true
     *  Condition 'null_tuple==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_tuple == NULL) {
        printf("NULL tuple returns NULL\n");
    }
    
    free_tuple(&t);
    
    return EXIT_SUCCESS;
}