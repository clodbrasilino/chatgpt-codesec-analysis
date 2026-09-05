#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    /* Possible weaknesses found:
     *  struct member 'Tuple::second' is never used. [unusedStructMember]
     */
    int second;
} Tuple;

int find_common_first(Tuple **lists, const int *sizes, int num_lists) {
    if (lists == NULL || sizes == NULL || num_lists <= 0) {
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
            return candidate;
        }
    }

    return -1;
}

int main(void) {
    Tuple list1[] = {{1, 2}, {3, 4}};
    Tuple list2[] = {{5, 6}, {3, 8}};
    Tuple list3[] = {{3, 10}, {7, 12}};

    int num_lists = 3;
    Tuple *lists[] = {list1, list2, list3};
    const int sizes[] = {2, 2, 2};

    int result = find_common_first(lists, sizes, num_lists);

    printf("%d\n", result);

    return 0;
}