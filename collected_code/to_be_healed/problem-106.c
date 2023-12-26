#include <stdio.h>

void addListToTuples(int list[], int tuples[][2], int listSize, int tuplesSize) {
    int i, j;
    
    for (i = 0; i < tuplesSize; i++) {
        for (j = 0; j < 2; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            tuples[i][j] += list[j];
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