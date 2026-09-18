#include <stdio.h>

void TupleExtractor(int *tupleOne, int *tupleTwo, int n) {
    for(int i=0; i<n; i++) {
        printf("Element %d of Tuple one is: %d \n", i+1, tupleOne[i]);
        printf("Element %d of Tuple two is: %d \n", i+1, tupleTwo[i]);
    }
}

int main() {
    int tupleOne[] = {1,2,3};
    int tupleTwo[] = {4,5,6};
    int n = sizeof(tupleOne) / sizeof(tupleOne[0]);

    TupleExtractor(tupleOne, tupleTwo, n);

    return 0;
} 