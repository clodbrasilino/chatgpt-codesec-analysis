#include <stdio.h>
#include <stdlib.h>

void findLargestN(int* dataSet, int dataSetSize, int* largestN, int n) {
    if(n<0 || n>dataSetSize){
        printf("Invalid n value\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        int maxIndex = 0;
        for (int j = 1; j < dataSetSize - i; j++) {
            if (dataSet[j] > dataSet[maxIndex]) {
                maxIndex = j;
            }
        }
        largestN[i] = dataSet[maxIndex];
        dataSet[maxIndex] = dataSet[dataSetSize - 1 - i];
    }
}

int main() {
    int dataSet[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int dataSetSize = sizeof(dataSet) / sizeof(dataSet[0]);
    int n = 5;
    int* largestN = (int*) malloc(n * sizeof(int));
    if(largestN == NULL){
        printf("Memory allocation failed\n");
        return -1;
    }
    findLargestN(dataSet, dataSetSize, largestN, n);
    for(int i = 0; i < n; i++) {
        printf("%d ", largestN[i]);
    }
    free(largestN);
    return 0;
}