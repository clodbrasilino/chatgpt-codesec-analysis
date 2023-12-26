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
    Tuple tupleList[3] = {
        {1, 2}, 
        {3, 4}, 
        {5, 6}
    };

    int totalSum = summationOfTupleElements(tupleList, 3);
    printf("Sum of tuple elements: %d\n", totalSum);
    
    return 0;
}