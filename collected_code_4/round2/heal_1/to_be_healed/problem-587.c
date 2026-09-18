#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'exit'
  */

typedef struct {
    int first;
    int second;
} Tuple;

Tuple convertToTuple(int* arr, int n) {
    if (n < 2) {
        printf("Array should have at least 2 elements\n");
        /* Possible weaknesses found:
         *  implicit declaration of function 'exit' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         */
        exit(0);
    }
    Tuple t;
    t.first = arr[0];
    t.second = arr[1];
    return t;
}

int main() {
    int arr[2] = {1, 2};
    Tuple t = convertToTuple(arr, 2);
    printf("Tuple elements are %d and %d\n", t.first, t.second);
    return 0;
}