#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
bool isMonotonic(int arr[], int n) {
    if (n <= 2) {
        return true;
    }
    
    int direction = 0;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i-1]) {
            if (direction == 0) {
                direction = 1;
            } else if (direction == -1) {
                return false;
            }
        } else if (arr[i] < arr[i-1]) {
            if (direction == 0) {
                direction = -1;
            } else if (direction == 1) {
                return false;
            }
        }
    }
    
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 2, 3};
    int arr2[] = {6, 5, 4, 4};
    int arr3[] = {1, 3, 2};
    int arr4[] = {1, 1, 1, 1};
    int arr5[] = {5};
    int arr6[] = {1, 2, 3, 4, 5, 6};
    int arr7[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int arr8[] = {1, 2, 3, 2, 1};
    
    printf("%d\n", isMonotonic(arr1, 4));
    printf("%d\n", isMonotonic(arr2, 4));
    printf("%d\n", isMonotonic(arr3, 3));
    printf("%d\n", isMonotonic(arr4, 4));
    printf("%d\n", isMonotonic(arr5, 1));
    printf("%d\n", isMonotonic(arr6, 6));
    printf("%d\n", isMonotonic(arr7, 9));
    printf("%d\n", isMonotonic(arr8, 5));
    
    return 0;
}