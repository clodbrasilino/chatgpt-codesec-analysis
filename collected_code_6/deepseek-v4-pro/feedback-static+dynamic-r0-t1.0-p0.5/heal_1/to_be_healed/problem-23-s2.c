#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
int max_sum_of_list(int **lists, int *sizes, int num_lists) {
    int max_sum = INT_MIN;
    int current_sum;
    int i, j;

    for (i = 0; i < num_lists; i++) {
        if (sizes[i] <= 0) {
            continue;
        }
        current_sum = 0;
        for (j = 0; j < sizes[i]; j++) {
            current_sum += lists[i][j];
        }
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {-1, -2, -3};
    int list3[] = {10, 20};
    int list4[] = {7};

    int *lists[] = {list1, list2, list3, list4};
    int sizes[] = {5, 3, 2, 1};
    int num_lists = 4;

    int result = max_sum_of_list(lists, sizes, num_lists);
    printf("%d\n", result);

    return 0;
}