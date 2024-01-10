#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void joinTuples(int tuples[][2], int numTuples) {
    assert(tuples != NULL && numTuples > 0);
        
    int i, j, k;
    for (i = 0; i < numTuples-1; i++) {
        for (j = 0; j < numTuples-i-1; j++) {
            if (tuples[j][0] > tuples[j+1][0]) {
                int temp[2] = {tuples[j][0], tuples[j][1]};
                tuples[j][0] = tuples[j+1][0];
                tuples[j][1] = tuples[j+1][1];
                tuples[j+1][0] = temp[0];
                tuples[j+1][1] = temp[1];
            }
        }
    }

    for (i = 0, k = 0; i < numTuples; i = j) {
        tuples[k][0] = tuples[i][0];
        tuples[k][1] = tuples[i][1];
        j = i + 1;
        while (j < numTuples && tuples[j][0] == tuples[i][0]) {
            tuples[k][1] += tuples[j][1];
            j++;
        }
        k++;
    }

    for (i = 0; i < k; i++) {
        printf("(%d, %d)\n", tuples[i][0], tuples[i][1]);
    }
}

int main() {
    int tuples[][2] = {
        {1, 5},
        {2, 3},
        {1, 2},
        {3, 4},
        {2, 1}
    };
    int numTuples = sizeof(tuples) / sizeof(tuples[0]);
    joinTuples(tuples, numTuples);
    return 0;
}