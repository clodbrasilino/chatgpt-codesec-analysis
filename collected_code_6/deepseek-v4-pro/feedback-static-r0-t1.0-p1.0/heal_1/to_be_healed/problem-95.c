#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int min_sublist_length(int arr[], int n, int target) {
    int min_length = INT_MAX;
    int current_sum = 0;
    int start = 0;
    
    if (n <= 0 || arr == NULL) {
        return -1;
    }
    
    for (int end = 0; end < n; end++) {
        current_sum += arr[end];
        
        while (current_sum >= target && start <= end) {
            int current_length = end - start + 1;
            if (current_length < min_length) {
                min_length = current_length;
            }
            current_sum -= arr[start];
            start++;
        }
    }
    
    return (min_length == INT_MAX) ? 0 : min_length;
}

int main(void) {
    int arr1[] = {2, 3, 1, 2, 4, 3};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int target1 = 7;
    printf("%d\n", min_sublist_length(arr1, n1, target1));
    
    int arr2[] = {1, 1, 1, 1, 1, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int target2 = 11;
    printf("%d\n", min_sublist_length(arr2, n2, target2));
    
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int target3 = 15;
    printf("%d\n", min_sublist_length(arr3, n3, target3));
    
    int *arr4 = NULL;
    printf("%d\n", min_sublist_length(arr4, 0, 5));
    
    return 0;
}