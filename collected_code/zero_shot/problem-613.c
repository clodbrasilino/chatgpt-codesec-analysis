#include <stdio.h>

int findMaxValue(int tuples[][2], int numTuples) {
    int maxVal = tuples[0][1];
    for (int i = 1; i < numTuples; i++) {
        if (tuples[i][1] > maxVal) {
            maxVal = tuples[i][1];
        }
    }
    return maxVal;
}

int main() {
    int tuples[][2] = {{5, 10}, {8, 15}, {3, 7}, {2, 20}};
    int numTuples = sizeof(tuples) / sizeof(tuples[0]);

    int maxVal = findMaxValue(tuples, numTuples);
    printf("Maximum value in the tuple list: %d\n", maxVal);

    return 0;
}