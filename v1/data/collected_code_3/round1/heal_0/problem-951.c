#include <stdio.h>

typedef struct {
    int x;
    int y;
} Tuple;

int max_of_similar_indices(Tuple* list1, Tuple* list2, int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (list1[i].x == list2[i].x && list1[i].y == list2[i].y) {
            if (i > max) {
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
    int max = max_of_similar_indices(list1, list2, size);
    printf("The maximum of similar indices is %d\n", max);
    return 0;
}