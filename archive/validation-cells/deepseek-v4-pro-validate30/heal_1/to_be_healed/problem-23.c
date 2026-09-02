#include <stdio.h>
#include <stdlib.h>

int max_subarray_sum(int *arr, int size) {
    if (size == 0) return 0;
    int max_so_far = arr[0];
    int current_max = arr[0];
    for (int i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Invalid test for overflow 'arr[i]>current_max+arr[i]'; signed integer overflow is undefined behavior. Some mainstream compilers removes handling of overflows when optimising the code and change the code to 'current_max<0'. [invalidTestForOverflow]
         */
        current_max = (arr[i] > current_max + arr[i]) ? arr[i] : current_max + arr[i];
        if (current_max > max_so_far) max_so_far = current_max;
    }
    return max_so_far;
}

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
int max_sum_of_lists(int **lists, int *sizes, int num_lists) {
    if (lists == NULL || sizes == NULL || num_lists <= 0) return 0;
    int max_sum = 0;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] == NULL || sizes[i] <= 0) continue;
        int sum = max_subarray_sum(lists[i], sizes[i]);
        if (i == 0 || sum > max_sum) max_sum = sum;
    }
    return max_sum;
}

int main(void) {
    int list1[] = {1, -2, 3, 4, -1, 2, 1, -5, 4};
    int list2[] = {-1, -3, -2, -4};
    int list3[] = {5, -1, 2, 3, -2};
    
    int sizes[] = {9, 4, 5};
    int *lists[] = {list1, list2, list3};
    
    int result = max_sum_of_lists(lists, sizes, 3);
    printf("%d\n", result);
    
    return 0;
}