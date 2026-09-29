#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int index;
    int value;
} Tuple;

void find_max_similar_indices(Tuple* list1, int size1, Tuple* list2, int size2) {
    if (!list1 || !list2 || size1 <= 0 || size2 <= 0) {
        return;
    }

    for (int i = 0; i < size1; ++i) {
        int max_val = INT_MIN;
        int found = 0;
        
        for (int j = 0; j < size2; ++j) {
            if (list1[i].index == list2[j].index) {
                int current_max = list1[i].value > list2[j].value ? list1[i].value : list2[j].value;
                if (current_max > max_val) {
                    max_val = current_max;
                }
                found = 1;
            }
        }
        
        if (found) {
            printf("Index %d: Max Value = %d\n", list1[i].index, max_val);
        }
    }
}

int main(void) {
    Tuple list1[] = {
        {1, 10},
        {2, 20},
        {3, 30},
        {4, 40}
    };
    
    Tuple list2[] = {
        {2, 25},
        {3, 28},
        {4, 50},
        {5, 60}
    };
    
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    
    find_max_similar_indices(list1, size1, list2, size2);
    
    return 0;
}