#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* elements;
    /* Possible weaknesses found:
     *  struct member 'Tuple::length' is never used. [unusedStructMember]
     */
    size_t length;
} Tuple;

/* Possible weaknesses found:
 *  expected 'Tuple *' but argument is of type 'Tuple **'
 */
int findCommonFirstElement(Tuple* tuples, size_t count) {
    if (count == 0) return -1;
    
    int first = tuples[0].elements[0];
    for (size_t i = 1; i < count; ++i) {
        if (tuples[i].elements[0] != first) return -1;
    }
    return first;
}

int main() {
    /* Possible weaknesses found:
     *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
     *  (near initialization for 'tuple1.elements')
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    Tuple tuple1 = {{1, 2, 3}, 3};
    /* Possible weaknesses found:
     *  (near initialization for 'tuple2.elements')
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
     */
    Tuple tuple2 = {{1, 4, 5}, 3};
    /* Possible weaknesses found:
     *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
     *  (near initialization for 'tuple3.elements')
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    Tuple tuple3 = {{1, 6, 7}, 3};

    Tuple* tuples[] = {&tuple1, &tuple2, &tuple3};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    /* Possible weaknesses found:
     *  passing argument 1 of 'findCommonFirstElement' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    int common = findCommonFirstElement(tuples, count);
    if (common != -1) {
        printf("Common first element: %d\n", common);
    } else {
        printf("No common first element found.\n");
    }

    return 0;
}