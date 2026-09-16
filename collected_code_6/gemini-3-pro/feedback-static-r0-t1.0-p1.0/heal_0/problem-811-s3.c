#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple* array;
    size_t size;
} TupleList;

bool are_tuple_lists_identical(const TupleList* list1, const TupleList* list2) {
    if (list1 == NULL || list2 == NULL) {
        return false;
    }
    
    if (list1->size != list2->size) {
        return false;
    }
    
    if (list1->array == NULL || list2->array == NULL) {
        return list1->array == list2->array;
    }
    
    for (size_t i = 0; i < list1->size; i++) {
        if (list1->array[i].x != list2->array[i].x || 
            list1->array[i].y != list2->array[i].y) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    Tuple arr1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple arr2[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple arr3[] = {{1, 2}, {3, 4}, {5, 7}};
    
    TupleList list1 = {arr1, 3};
    TupleList list2 = {arr2, 3};
    TupleList list3 = {arr3, 3};
    
    if (are_tuple_lists_identical(&list1, &list2)) {
        printf("List 1 and List 2 are identical\n");
    } else {
        printf("List 1 and List 2 are not identical\n");
    }
    
    if (are_tuple_lists_identical(&list1, &list3)) {
        printf("List 1 and List 3 are identical\n");
    } else {
        printf("List 1 and List 3 are not identical\n");
    }
    
    return 0;
}