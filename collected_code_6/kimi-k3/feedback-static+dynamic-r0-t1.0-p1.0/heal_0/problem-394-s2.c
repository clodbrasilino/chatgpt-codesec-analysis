#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int is_distinct(const Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL || tuple->size == 0) {
        return 0;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        for (size_t j = i + 1; j < tuple->size; j++) {
            if (tuple->elements[i] == tuple->elements[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {
    int data1[] = {1, 2, 3, 4, 5};
    int data2[] = {1, 2, 3, 2, 5};
    int data3[] = {7};
    
    Tuple t1 = {data1, sizeof(data1) / sizeof(data1[0])};
    Tuple t2 = {data2, sizeof(data2) / sizeof(data2[0])};
    Tuple t3 = {data3, sizeof(data3) / sizeof(data3[0])};
    Tuple t4 = {NULL, 0};
    
    printf("Tuple 1: %s\n", is_distinct(&t1) ? "distinct" : "not distinct");
    printf("Tuple 2: %s\n", is_distinct(&t2) ? "distinct" : "not distinct");
    printf("Tuple 3: %s\n", is_distinct(&t3) ? "distinct" : "not distinct");
    printf("Tuple 4: %s\n", is_distinct(&t4) ? "distinct" : "not distinct");
    
    return EXIT_SUCCESS;
}