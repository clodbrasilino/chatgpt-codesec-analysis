#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

bool is_distinct(const Tuple *t) {
    if (t == NULL || t->elements == NULL || t->size == 0) {
        return false;
    }
    
    for (size_t i = 0; i < t->size; i++) {
        for (size_t j = i + 1; j < t->size; j++) {
            if (t->elements[i] == t->elements[j]) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 2, 5};
    int arr3[] = {7};
    
    Tuple t1 = {arr1, 5};
    Tuple t2 = {arr2, 5};
    Tuple t3 = {arr3, 1};
    Tuple t4 = {NULL, 0};
    
    printf("Tuple 1 is distinct: %s\n", is_distinct(&t1) ? "true" : "false");
    printf("Tuple 2 is distinct: %s\n", is_distinct(&t2) ? "true" : "false");
    printf("Tuple 3 is distinct: %s\n", is_distinct(&t3) ? "true" : "false");
    printf("Tuple 4 is distinct: %s\n", is_distinct(&t4) ? "true" : "false");
    
    return EXIT_SUCCESS;
}