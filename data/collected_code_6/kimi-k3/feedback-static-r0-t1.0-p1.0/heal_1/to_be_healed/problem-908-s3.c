#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findFixedPoint(int arr[], int n) {
    int low = 0;
    int high = n - 1;
    int result = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == mid) {
            result = mid;
            high = mid - 1;
        } else if (arr[mid] < mid) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return result;
}

int main(void) {
    int arr[] = {-10, -5, 0, 3, 7};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr)/sizeof(arr[0])', assigned value is 5
     */
    int n = sizeof(arr) / sizeof(arr[0]);
    
    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     */
    if (n <= 0) {
        fprintf(stderr, "Invalid array size\n");
        return EXIT_FAILURE;
    }
    
    int fixedPoint = findFixedPoint(arr, n);
    
    if (fixedPoint != -1) {
        printf("Fixed point is %d\n", fixedPoint);
    } else {
        printf("No fixed point found\n");
    }
    
    return EXIT_SUCCESS;
}