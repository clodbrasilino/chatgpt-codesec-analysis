#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int check_sortable_by_corners(int arr[], int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    
    int left = 0;
    int right = n - 1;
    int prev;
    int initialized = 0;
    int sorted_arr[n];
    int idx = 0;
    
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (left <= right) {
        int selected;
        int can_take_left = 1;
        int can_take_right = 1;
        
        if (initialized) {
            if (arr[left] < prev) can_take_left = 0;
            if (arr[right] < prev) can_take_right = 0;
            if (left == right) {
                can_take_right = can_take_left;
            }
        }
        
        if (can_take_left && can_take_right) {
            if (arr[left] <= arr[right]) {
                selected = arr[left];
                left++;
            } else {
                selected = arr[right];
                right--;
            }
        } else if (can_take_left) {
            selected = arr[left];
            left++;
        } else if (can_take_right) {
            selected = arr[right];
            right--;
        } else {
            return 0;
        }
        
        sorted_arr[idx++] = selected;
        if (!initialized) {
            initialized = 1;
            prev = selected;
        } else {
            if (selected < prev) return 0;
            prev = selected;
        }
    }
    
    for (int i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Uninitialized variable: sorted_arr
         *  Uninitialized variable: sorted_arr [uninitvar]
         */
        if (sorted_arr[i] < sorted_arr[i-1]) return 0;
    }
    
    return 1;
}

int main(void) {
    int test1[] = {2, 3, 1, 4};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    printf("%d\n", check_sortable_by_corners(test1, n1));
    
    int test2[] = {1, 2, 3, 4};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    printf("%d\n", check_sortable_by_corners(test2, n2));
    
    int test3[] = {4, 1, 2, 3};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    printf("%d\n", check_sortable_by_corners(test3, n3));
    
    int test4[] = {3, 1, 4, 2};
    int n4 = sizeof(test4) / sizeof(test4[0]);
    printf("%d\n", check_sortable_by_corners(test4, n4));
    
    int test5[] = {1};
    int n5 = sizeof(test5) / sizeof(test5[0]);
    printf("%d\n", check_sortable_by_corners(test5, n5));
    
    return 0;
}