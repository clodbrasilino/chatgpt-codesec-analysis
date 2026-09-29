#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

int tuple_contains_k(const Tuple *t, int k) {
    if (t == NULL || t->elements == NULL || t->size <= 0) {
        return 0;
    }
    for (int i = 0; i < t->size; i++) {
        if (t->elements[i] == k) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, 20, 30};
    int arr3[] = {7};
    
    Tuple t1 = {arr1, 5};
    Tuple t2 = {arr2, 3};
    Tuple t3 = {arr3, 1};
    
    printf("t1 contains 3: %s\n", tuple_contains_k(&t1, 3) ? "yes" : "no");
    printf("t1 contains 10: %s\n", tuple_contains_k(&t1, 10) ? "yes" : "no");
    printf("t2 contains 20: %s\n", tuple_contains_k(&t2, 20) ? "yes" : "no");
    printf("t3 contains 7: %s\n", tuple_contains_k(&t3, 7) ? "yes" : "no");
    printf("t3 contains 8: %s\n", tuple_contains_k(&t3, 8) ? "yes" : "no");
    
    const Tuple *null_tuple = NULL;
    /* Possible weaknesses found:
     *  Assignment 'result=tuple_contains_k(null_tuple,1)', assigned value is 0
     *  Calling function 'tuple_contains_k' returns 0
     */
    int result = tuple_contains_k(null_tuple, 1);
    /* Possible weaknesses found:
     *  Condition 'result' is always false
     *  Condition 'result' is always false [knownConditionTrueFalse]
     */
    if (result) {
        printf("null tuple contains 1: yes\n");
    } else {
        printf("null tuple contains 1: no\n");
    }
    
    return 0;
}