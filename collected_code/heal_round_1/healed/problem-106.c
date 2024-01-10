#include <stdio.h>

void addListToTuples(const int list[], int tuples[][2], int listSize, int tuplesSize) {
    int i, j;
    
    for (i = 0; i < tuplesSize; i++) {
        for (j = 0; j < 2; j++) {
            tuples[i][j] += list[j % listSize];
        }
    }
}

int main() {
    int list[2] = {10, 20};
    int tuples[2][2] = {{1, 2}, {3, 4}};
    int i, j;
    
    addListToTuples(list, tuples, sizeof(list) / sizeof(int), sizeof(tuples) / sizeof(tuples[0]));
    
    for (i = 0; i < sizeof(tuples) / sizeof(tuples[0]); i++) {
        for (j = 0; j < 2; j++) {
            printf("%d ", tuples[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}