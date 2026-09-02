#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool can_sort_by_corners(const int *arr, int n) {
    if (n <= 1) return true;
    
    int last = -1;
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        int chosen;
        
        if (arr[left] <= arr[right]) {
            chosen = arr[left];
            left++;
        } else {
            chosen = arr[right];
            right--;
        }
        
        if (last != -1 && chosen < last) {
            return false;
        }
        
        last = chosen;
    }
    
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {5, 1, 2, 3, 4};
    int arr3[] = {3, 1, 5, 2, 4};
    int arr4[] = {1};
    int arr5[] = {2, 1, 3};
    
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    /* Possible weaknesses found:
     *  Assignment 'n4=sizeof(arr4)/sizeof(arr4[0])', assigned value is 1
     */
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    
    bool result1 = can_sort_by_corners(arr1, n1);
    bool result2 = can_sort_by_corners(arr2, n2);
    bool result3 = can_sort_by_corners(arr3, n3);
    
    /* Possible weaknesses found:
     *  Condition 'n4==1' is always true [knownConditionTrueFalse]
     *  Condition 'n4==1' is always true
     */
    if (n4 == 1) {
        printf("true\n");
    } else {
        bool result4 = can_sort_by_corners(arr4, n4);
        printf("%s\n", result4 ? "true" : "false");
    }
    
    bool result5 = can_sort_by_corners(arr5, n5);
    
    printf("%s\n", result1 ? "true" : "false");
    printf("%s\n", result2 ? "true" : "false");
    printf("%s\n", result3 ? "true" : "false");
    printf("%s\n", result5 ? "true" : "false");
    
    return 0;
}