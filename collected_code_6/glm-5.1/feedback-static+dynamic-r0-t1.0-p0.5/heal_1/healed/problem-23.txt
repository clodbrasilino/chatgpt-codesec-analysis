#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_sum_of_lists(int * const *lists, const int *sizes, int num_lists) {
    if (lists == NULL || sizes == NULL || num_lists <= 0) {
        return 0;
    }

    int max_sum = INT_MIN;

    for (int i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            continue;
        }

        int current_sum = 0;
        for (int j = 0; j < sizes[i]; j++) {
            current_sum += lists[i][j];
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

int main(void) {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {-1, -2, -3, -4};
    int list4[] = {10};

    int *lists[] = {list1, list2, list3, list4};
    int sizes[] = {3, 2, 4, 1};
    int num_lists = 4;

    int result = max_sum_of_lists(lists, sizes, num_lists);
    printf("%d\n", result);

    return 0;
}