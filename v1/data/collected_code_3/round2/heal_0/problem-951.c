#include <stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

int maxSimilarIndices(Tuple* list1, Tuple* list2, int size) {
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
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    Tuple list2[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int size = sizeof(list1) / sizeof(Tuple);
    int maxIndex = maxSimilarIndices(list1, list2, size);
    printf("The maximum index of similar tuples is: %d\n", maxIndex);
    return 0;
}