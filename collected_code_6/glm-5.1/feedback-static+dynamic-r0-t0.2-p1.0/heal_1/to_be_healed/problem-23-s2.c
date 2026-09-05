#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
int max_sum_of_lists(int **lists, int *sizes, int num_lists) {
    if (lists == NULL || sizes == NULL || num_lists <= 0) {
        return 0;
    }

    int max_sum = 0;
    int initialized = 0;

    for (int i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            continue;
        }

        int current_sum = 0;
        for (int j = 0; j < sizes[i]; j++) {
            current_sum += lists[i][j];
        }

        if (!initialized) {
            max_sum = current_sum;
            initialized = 1;
        } else if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6, 7};
    int list3[] = {-1, -2, -3};
    
    int *lists[] = {list1, list2, list3};
    int sizes[] = {3, 4, 3};
    int num_lists = 3;

    int result = max_sum_of_lists(lists, sizes, num_lists);
    printf("%d\n", result);

    return 0;
}