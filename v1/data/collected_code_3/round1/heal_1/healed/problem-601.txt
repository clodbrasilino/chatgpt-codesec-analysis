#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int maxChainLength(int pairs[MAX][2], int n) {
    int i, j, max = 0;
    int *mcl = (int*) malloc(sizeof(int) * n);

    if(mcl == NULL){
        return -1;
    }

    for (i = 0; i < n; i++)
        mcl[i] = 1;

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (pairs[i][0] > pairs[j][1] && mcl[i] < mcl[j] + 1)
                mcl[i] = mcl[j] + 1;

    for (i = 0; i < n; i++)
        if (max < mcl[i])
            max = mcl[i];

    free(mcl);

    return max;
}

int main() {
    int pairs[MAX][2] = { {5, 24}, {15, 25}, {27, 40}, {50, 60} };
    int n = sizeof(pairs)/sizeof(pairs[0]);
    int result = maxChainLength(pairs, n);
    if(result != -1){
        printf("Length of maximum size chain is %d\n", result);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}