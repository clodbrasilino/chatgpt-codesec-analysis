#include <stdio.h>

#define SIZE 5

void addTuples(int src1[][SIZE], int src2[][SIZE], int size, int result[][SIZE]) {
    if (!src1 || !src2 || !result || size <= 0) {
        return;
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = src1[i][j] + src2[i][j];
        }
    }
}

int main() {
    int src1[][SIZE] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};
    int src2[][SIZE] = {{10, 20, 30, 40, 50}, {60, 70, 80, 90, 100}};
    int size = sizeof(src1) / (sizeof(int) * SIZE);
    int result[size][SIZE];

    addTuples(src1, src2, size, result);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        
        printf("\n");
    }
    
    return 0;
}