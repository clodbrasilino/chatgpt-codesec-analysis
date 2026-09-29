#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int id;
    int value;
} Tuple;

int find_max_similar_indices(Tuple* list1, int size1, Tuple* list2, int size2, int target_id) {
    if (list1 == NULL || list2 == NULL || size1 < 0 || size2 < 0) {
        return INT_MIN;
    }

    int max_val = INT_MIN;
    int min_size = size1 < size2 ? size1 : size2;

    for (int i = 0; i < min_size; i++) {
        if (list1[i].id == target_id && list2[i].id == target_id) {
            if (list1[i].value > max_val) {
                max_val = list1[i].value;
            }
            if (list2[i].value > max_val) {
                max_val = list2[i].value;
            }
        }
    }

    return max_val;
}

int main(void) {
    Tuple list1[] = {
        {1, 10},
        {2, 20},
        {3, 30}
    };
    
    Tuple list2[] = {
        {1, 15},
        {2, 25},
        {4, 40}
    };

    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);

    int target_id = 2;
    int max_val = find_max_similar_indices(list1, size1, list2, size2, target_id);

    if (max_val != INT_MIN) {
        printf("Maximum value for id %d at similar indices: %d\n", target_id, max_val);
    } else {
        printf("No matching tuples found at similar indices for id %d.\n", target_id);
    }

    return 0;
}