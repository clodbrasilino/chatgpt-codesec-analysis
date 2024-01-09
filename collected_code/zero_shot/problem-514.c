#include <stdio.h>

typedef struct {
    int x, y;
} Tuple;

int summationOfTupleElements(Tuple tupleList[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += tupleList[i].x + tupleList[i].y;
    }
    return sum;
}

int main() {
    Tuple tupleList[3];
    
    tupleList[0].x = 1;
    tupleList[0].y = 2;
    
    tupleList[1].x = 3;
    tupleList[1].y = 4;
    
    tupleList[2].x = 5;
    tupleList[2].y = 6;
    
    int totalSum = summationOfTupleElements(tupleList, 3);
    printf("Sum of tuple elements: %d\n", totalSum);
    
    return 0;
}