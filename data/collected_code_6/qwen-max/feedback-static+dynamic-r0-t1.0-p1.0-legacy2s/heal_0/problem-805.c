#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t count;
} IntList;

IntList* findMaxSumList(IntList *lists, size_t n) {
    if (n == 0) return NULL;
    IntList *maxList = lists;
    int maxSum = 0;
    for (size_t i = 0; i < n; ++i) {
        int sum = 0;
        for (size_t j = 0; j < lists[i].count; ++j) {
            sum += lists[i].elements[j];
        }
        if (sum > maxSum) {
            maxSum = sum;
            maxList = &lists[i];
        }
    }
    return maxList;
}

int main() {
    IntList lists[] = {
        {{1, 2, 3}, 3},
        {{4, 5, 6, 7}, 4},
        {{8, 9}, 2},
        {{-1, -2, -3}, 3}
    };
    size_t n = sizeof(lists) / sizeof(lists[0]);
    
    IntList *maxList = findMaxSumList(lists, n);
    
    printf("Max Sum List: [");
    for (size_t i = 0; i < maxList->count; ++i) {
        printf("%d%s", maxList->elements[i], i < maxList->count - 1 ? ", " : "");
    }
    printf("]\n");
    
    return 0;
}