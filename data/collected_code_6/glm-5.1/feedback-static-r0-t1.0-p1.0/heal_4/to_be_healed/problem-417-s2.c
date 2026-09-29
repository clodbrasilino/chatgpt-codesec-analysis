#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    /* Possible weaknesses found:
     *  struct member 'Tuple::second' is never used. [unusedStructMember]
     */
    int second;
} Tuple;

int find_common_first(Tuple **lists, const int *sizes, int num_lists, int *common_val) {
    if (num_lists == 0 || lists == NULL || sizes == NULL) {
        return -1;
    }

    for (int i = 0; i < sizes[0]; i++) {
        int candidate = lists[0][i].first;
        int is_common = 1;

        for (int j = 1; j < num_lists; j++) {
            int found = 0;
            for (int k = 0; k < sizes[j]; k++) {
                if (lists[j][k].first == candidate) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                is_common = 0;
                break;
            }
        }

        if (is_common) {
            *common_val = candidate;
            return 0;
        }
    }

    return -1;
}

int main() {
    Tuple list1[] = {{3, 1}, {5, 2}, {8, 3}};
    Tuple list2[] = {{9, 4}, {5, 5}, {7, 6}};
    Tuple list3[] = {{5, 7}, {2, 8}, {1, 9}};
    
    const int sizes[] = {3, 3, 3};
    Tuple *lists[] = {list1, list2, list3};
    
    int common_val;
    int result = find_common_first(lists, sizes, 3, &common_val);
    
    if (result == 0) {
        printf("%d\n", common_val);
    } else {
        printf("No common first element found\n");
    }
    
    return 0;
}