#include <stdio.h>

typedef struct {
    int index;
    int value;
} Tuple;

int getMinValueIndex(Tuple tuples[], int size) {
    int minIdx = 0;
    int minValue = tuples[0].value;
    
    for (int i = 1; i < size; i++) {
        if (tuples[i].value < minValue) {
            minValue = tuples[i].value;
            minIdx = i;
        }
    }
    
    return minIdx;
}

int main() {
    Tuple tuples[] = {{0, 5}, {1, 3}, {2, 7}, {3, 2}, {4, 6}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    
    int minIdx = getMinValueIndex(tuples, size);
    
    printf("Index of minimum value record: %d\n", minIdx);
    
    return 0;
}