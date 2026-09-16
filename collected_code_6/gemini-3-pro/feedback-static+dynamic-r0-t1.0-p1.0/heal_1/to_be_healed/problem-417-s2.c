#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    /* Possible weaknesses found:
     *  struct member 'Tuple::second' is never used. [unusedStructMember]
     */
    int second;
} Tuple;

int findCommonFirstElement(Tuple* tuples, size_t size, int* result) {
    if (tuples == NULL || size == 0 || result == NULL) {
        return 0;
    }

    int common = tuples[0].first;

    for (size_t i = 1; i < size; ++i) {
        if (tuples[i].first != common) {
            return 0; 
        }
    }

    *result = common;
    return 1; 
}

int main(void) {
    Tuple tuples1[] = {{5, 1}, {5, 2}, {5, 3}};
    size_t size1 = sizeof(tuples1) / sizeof(tuples1[0]);
    int result1;

    if (findCommonFirstElement(tuples1, size1, &result1)) {
        printf("%d\n", result1);
    } else {
        printf("No common first element\n");
    }

    Tuple tuples2[] = {{5, 1}, {4, 2}, {5, 3}};
    size_t size2 = sizeof(tuples2) / sizeof(tuples2[0]);
    int result2;

    if (findCommonFirstElement(tuples2, size2, &result2)) {
        printf("%d\n", result2);
    } else {
        printf("No common first element\n");
    }

    return 0;
}