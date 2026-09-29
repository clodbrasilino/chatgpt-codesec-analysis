#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

int compare(const void *a, const void *b) {
    return ((Range *)a)->start - ((Range *)b)->start;
}

int* findMissingRanges(Range *ranges, int rangesSize, int start, int end, int *returnSize) {
    int *missingRanges = (int *)malloc((end - start + 1) * sizeof(int));
    int currentIndex = 0;
    
    for (int i = start; i <= end; i++) {
        if (currentIndex < rangesSize && i >= ranges[currentIndex].start && i <= ranges[currentIndex].end) {
            if (i == ranges[currentIndex].end) {
                currentIndex++;
            }
        } else {
            missingRanges[i - start] = i;
        }
    }
    
    *returnSize = 0;
    for (int i = 0; i <= end - start; i++) {
        if (missingRanges[i] != 0) {
            *returnSize += 1;
        }
    }
    
    int *result = (int *)malloc(*returnSize * sizeof(int));
    int resultIndex = 0;
    for (int i = 0; i <= end - start; i++) {
        if (missingRanges[i] != 0) {
            result[resultIndex++] = missingRanges[i];
        }
    }
    
    free(missingRanges);
    return result;
}

int main() {
    Range ranges[] = {{3, 5}, {20, 22}};
    int rangesSize = 2;
    int start = 1;
    int end = 25;
    int returnSize = 0;
    
    Range sortedRanges[2];
    for (int i = 0; i < rangesSize; i++) {
        sortedRanges[i] = ranges[i];
    }
    qsort(sortedRanges, rangesSize, sizeof(Range), compare);
    
    int *missingRanges = findMissingRanges(sortedRanges, rangesSize, start, end, &returnSize);
    
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", missingRanges[i]);
    }
    printf("\n");
    
    free(missingRanges);
    return 0;
}