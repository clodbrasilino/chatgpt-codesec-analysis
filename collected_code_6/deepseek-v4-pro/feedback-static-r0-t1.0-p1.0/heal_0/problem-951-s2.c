#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Tuple;

int find_max_similar_indices(Tuple *list1, int size1, Tuple *list2, int size2) {
    if (list1 == NULL || list2 == NULL) {
        return -1;
    }
    
    int max_value = -1;
    int min_size = (size1 < size2) ? size1 : size2;
    
    for (int i = 0; i < min_size; i++) {
        if (list1[i].value == list2[i].value) {
            if (list1[i].value > max_value) {
                max_value = list1[i].value;
            }
        }
    }
    
    return max_value;
}

int main(void) {
    Tuple list1[] = {{5}, {2}, {8}, {1}, {9}};
    Tuple list2[] = {{5}, {7}, {8}, {3}, {9}, {10}};
    
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    
    int result = find_max_similar_indices(list1, size1, list2, size2);
    
    printf("Maximum of similar indices: %d\n", result);
    
    return 0;
}