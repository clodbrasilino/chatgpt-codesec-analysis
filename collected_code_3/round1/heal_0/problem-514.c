#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

int sumTupleElements(Tuple* tupleList, int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += tupleList[i].a + tupleList[i].b;
    }
    return sum;
}

int main() {
    Tuple tupleList[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int size = sizeof(tupleList) / sizeof(Tuple);
    int sum = sumTupleElements(tupleList, size);
    printf("Sum of tuple elements: %d\n", sum);
    return 0;
}