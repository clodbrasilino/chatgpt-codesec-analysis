#include <stdio.h>

void printTuple(int tuple[], int size) {
    printf("(");
    
    for (int i = 0; i < size; i++) {
        if (i != size - 1) {
            printf("%d, ", tuple[i]);
        } else {
            printf("%d", tuple[i]);
        }
    }
    
    printf(")\n");
}

void findCombinations(int tupleList[][2], int size, int index, int tuple[], int tupleSize, int targetSum) {
    if (tupleSize == 2) {
        if (tuple[0] + tuple[1] == targetSum) {
            printTuple(tuple, tupleSize);
        }
        return;
    }
    
    if (index >= size) {
        return;
    }
    
    tuple[tupleSize] = tupleList[index][0];
    findCombinations(tupleList, size, index + 1, tuple, tupleSize + 1, targetSum);
    
    tuple[tupleSize] = tupleList[index][1];
    findCombinations(tupleList, size, index + 1, tuple, tupleSize + 1, targetSum);
    
    findCombinations(tupleList, size, index + 1, tuple, tupleSize, targetSum);
}

void findCombinationsWrapper(int tupleList[][2], int size, int targetSum) {
    int tuple[2];
    findCombinations(tupleList, size, 0, tuple, 0, targetSum);
}

int main() {
    int tupleList[][2] = {{1, 2}, {2, 3}, {4, 5}, {6, 7}};
    int size = sizeof(tupleList) / sizeof(tupleList[0]);
    int targetSum = 7;
    
    findCombinationsWrapper(tupleList, size, targetSum);
    
    return 0;
}