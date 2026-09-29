#include <stdio.h>

typedef struct {
    int index;
    int value;
} Tuple;

Tuple findMinIndex(Tuple tuples[], int size) {
    Tuple minIndex = tuples[0];
    for(int i = 1; i < size; i++) {
        if(tuples[i].value < minIndex.value) {
            minIndex = tuples[i];
        }
    }
    return minIndex;
}

int main() {
    Tuple tuples[] = {{0, 10}, {1, 20}, {2, 5}, {3, 15}, {4, 30}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    Tuple minIndex = findMinIndex(tuples, size);
    printf("Index: %d, Value: %d\n", minIndex.index, minIndex.value);
    return 0;
}