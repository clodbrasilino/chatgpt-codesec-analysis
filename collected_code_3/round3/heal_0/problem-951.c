#include <stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_max_of_similar_indices(Tuple* list1, Tuple* list2, int size) {
    int max = 0;
    for(int i = 0; i < size; i++) {
        if(list1[i].first == list2[i].first && list1[i].second == list2[i].second) {
            if(list1[i].first > max) {
                max = list1[i].first;
            }
            if(list1[i].second > max) {
                max = list1[i].second;
            }
        }
    }
    return max;
}

int main() {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple list2[] = {{1, 2}, {7, 8}, {5, 6}};
    int size = sizeof(list1) / sizeof(Tuple);
    int max = find_max_of_similar_indices(list1, list2, size);
    printf("Max of similar indices: %d\n", max);
    return 0;
}