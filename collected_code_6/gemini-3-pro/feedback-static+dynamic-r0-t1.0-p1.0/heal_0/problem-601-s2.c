#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int a;
    int b;
};

int comparePairs(const void *p1, const void *p2) {
    return ((struct Pair *)p1)->a - ((struct Pair *)p2)->a;
}

int findLongestChain(struct Pair arr[], int n) {
    if (n == 0) return 0;
    
    int *mcl = (int *)malloc(sizeof(int) * n);
    if (!mcl) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    int i, j, max = 0;
    
    qsort(arr, n, sizeof(struct Pair), comparePairs);
    
    for (i = 0; i < n; i++) {
        mcl[i] = 1;
    }
    
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[i].a > arr[j].b && mcl[i] < mcl[j] + 1) {
                mcl[i] = mcl[j] + 1;
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        if (max < mcl[i]) {
            max = mcl[i];
        }
    }
    
    free(mcl);
    
    return max;
}

int main(void) {
    struct Pair arr[] = {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}};
    int n = sizeof(arr) / sizeof(arr[0]);
    int longestChainLength = findLongestChain(arr, n);
    
    printf("Length of maximum size chain is %d\n", longestChainLength);
    
    return 0;
}