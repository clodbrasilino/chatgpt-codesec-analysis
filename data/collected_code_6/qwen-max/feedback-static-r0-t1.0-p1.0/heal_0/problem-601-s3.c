#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int**)a)[1] - (*(int**)b)[1];
}

int findLongestChain(int** pairs, int pairsSize, int* pairsColSize){
    qsort(pairs, pairsSize, sizeof(pairs[0]), cmp);
    
    int currentEnd = pairs[0][1];
    int count = 1;
    
    for (int i = 1; i < pairsSize; i++) {
        if (pairs[i][0] > currentEnd) {
            currentEnd = pairs[i][1];
            count++;
        }
    }
    
    return count;
}

int main() {
    int pairs[][2] = {{1, 2}, {2, 3}, {3, 4}};
    int pairsSize = 3;
    int pairsColSize = 2;

    int result = findLongestChain((int**)pairs, pairsSize, &pairsColSize);
    printf("The length of the longest chain is: %d\n", result);

    return 0;
}