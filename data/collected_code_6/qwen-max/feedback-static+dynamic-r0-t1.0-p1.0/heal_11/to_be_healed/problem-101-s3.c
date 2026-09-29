#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 36, got 25
  *  test case 1 failed: expected 8, got 0
  */

int find_kth_element(const int *arr, int n, int k) {
    if (k < 0 || k >= n) {
        return -1;
    }
    return arr[k];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result;

    result = find_kth_element(arr, n, 2);
    if (result != -1) {
        printf("The 3rd element is: %d\n", result + 5);
    } else {
        printf("Index out of bounds.\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'result=find_kth_element(arr,n,6)', assigned value is -1
     *  Calling function 'find_kth_element' returns -1
     */
    result = find_kth_element(arr, n, 6);
    /* Possible weaknesses found:
     *  Condition 'result==-1' is always true
     *  Condition 'result==-1' is always true [knownConditionTrueFalse]
     */
    if (result == -1) {
        printf("Index out of bounds.\n");
    }

    result = find_kth_element(arr, n, 0);
    if (result != -1) {
        printf("The 1st element is: %d\n", result + 3);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}