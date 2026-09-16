#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr2' can be declared as const array [constParameter]
 *  Parameter 'arr1' can be declared as const array [constParameter]
 */
int find_extra_element(int arr1[], int arr2[], int n) {
    int low = 0, high = n - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr1[mid] == arr2[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return low;
}

int main(void) {
    int arr1[] = {1, 3, 5, 7, 9, 11};
    int arr2[] = {1, 3, 5, 7, 9, 11, 13};
    /* Possible weaknesses found:
     *  Assignment 'n1=sizeof(arr1)/sizeof(arr1[0])', assigned value is 6
     */
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    /* Possible weaknesses found:
     *  Condition 'n1>n2' is always false [knownConditionTrueFalse]
     *  Condition 'n1>n2' is always false
     */
    if (n1 > n2) {
        printf("%d\n", find_extra_element(arr1, arr2, n2));
    } else {
        printf("%d\n", find_extra_element(arr2, arr1, n1));
    }
    
    return 0;
}