#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_sum_of_list(int **lists, const int *sizes, int num_lists) {
    int max_sum = INT_MIN;
    int i, j;
    
    for (i = 0; i < num_lists; i++) {
        int current_sum = 0;
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
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {-1, -2, -3, -4};
    int list4[] = {10, 20, 30, 40, 50};
    
    int *lists[] = {list1, list2, list3, list4};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    int sizes[] = {3, 2, 4, 5};
    int num_lists = 4;
    
    int result = max_sum_of_list(lists, sizes, num_lists);
    printf("Maximum sum: %d\n", result);
    
    return 0;
}