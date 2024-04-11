#include <stdio.h>

typedef struct {
    int first;
    int second;
} Pair;

int findMaxOfSimilarIndices(Pair *list1, Pair *list2, int size) {
    int max = -1;
    for(int i = 0; i < size; i++) {
        if(list1[i].first == list2[i].first && list1[i].second == list2[i].second) {
            if(i > max) {
                max = i;
            }
        }
    }
    return max;
}

int main() {
    Pair list1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    Pair list2[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int size = sizeof(list1) / sizeof(Pair);
    int maxIndex = findMaxOfSimilarIndices(list1, list2, size);
    printf("Max index of similar pairs: %d\n", maxIndex);
    return 0;
}