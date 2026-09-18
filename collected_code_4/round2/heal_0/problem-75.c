#include<stdio.h>
#include<stdbool.h>

#define SIZE 3

bool checkDivisibility(int tuple[], int tupleSize, int k) {
    for(int i=0; i<tupleSize; i++) {
        if(tuple[i] % k != 0) {
            return false;
        }
    }
    return true;
}

void findDivisibleTuples(int tuples[][SIZE], int numOfTuples, int tupleSize, int k) {
    for(int i=0; i<numOfTuples; i++) {
        if(checkDivisibility(tuples[i], tupleSize, k)) {
            printf("Tuple %d is divisible by %d: [", i+1, k);
            for(int j=0; j<tupleSize; j++) {
                printf(" %d ", tuples[i][j]);
            }
            printf("]\n");
        }
    }
}

int main() {
    int tuples[4][SIZE] = {{5, 10, 15}, {20, 35, 50}, {65, 45, 75}, {80, 95, 100}};
    int numOfTuples = sizeof(tuples) / sizeof(tuples[0]);
    int divisor = 5;
    findDivisibleTuples(tuples, numOfTuples, SIZE, divisor);
    return 0;
}