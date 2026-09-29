#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int findMaxOccurringDivisor(int start, int end, int *maxCount) {
    if (start > end || start < 1 || maxCount == NULL) {
        return -1;
    }
    
    int range = end - start + 1;
    int *counts = calloc((size_t)range, sizeof(int));
    if (counts == NULL) {
        return -1;
    }
    
    for (int i = start; i <= end; i++) {
        for (int j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                counts[i - start]++;
                if (j != i / j) {
                    counts[i - start]++;
                }
            }
        }
    }
    
    int maxIdx = 0;
    *maxCount = counts[0];
    
    for (int i = 1; i < range; i++) {
        if (counts[i] > *maxCount) {
            *maxCount = counts[i];
            maxIdx = i;
        }
    }
    
    free(counts);
    return start + maxIdx;
}

int main(void) {
    int start, end;
    
    if (scanf("%d %d", &start, &end) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (start < 1 || end < 1 || start > end) {
        fprintf(stderr, "Invalid range\n");
        return EXIT_FAILURE;
    }
    
    int maxCount;
    int result = findMaxOccurringDivisor(start, end, &maxCount);
    
    if (result == -1) {
        fprintf(stderr, "Error processing range\n");
        return EXIT_FAILURE;
    }
    
    printf("%d %d\n", result, maxCount);
    
    return EXIT_SUCCESS;
}