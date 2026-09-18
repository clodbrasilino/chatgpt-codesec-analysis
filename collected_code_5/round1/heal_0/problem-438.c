#include <stdio.h>

int countBidirectionalPairs(int array[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] == array[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int testArray[] = {1, 2, 3, 2, 1, 3, 4, 4};
    int size = sizeof(testArray)/sizeof(testArray[0]);
    
    int bidirectionalPairs = countBidirectionalPairs(testArray, size);
    
    printf("Number of bidirectional pairs: %d\n", bidirectionalPairs);
    
    return 0;
}