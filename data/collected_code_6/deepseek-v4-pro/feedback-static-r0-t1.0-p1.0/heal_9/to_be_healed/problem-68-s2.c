#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool isMonotonic(const int *arr, size_t size) {
    if (size <= 1) {
        return true;
    }
    
    if (arr == NULL) {
        return false;
    }
    
    bool increasing = true;
    bool decreasing = true;
    
    for (size_t i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            increasing = false;
        }
        if (arr[i] < arr[i + 1]) {
            decreasing = false;
        }
    }
    
    return increasing || decreasing;
}

int main(void) {
    const int arr1[] = {1, 2, 3, 4, 5};
    const int arr2[] = {5, 4, 3, 2, 1};
    const int arr3[] = {1, 2, 2, 3, 4};
    const int arr4[] = {1, 3, 2, 4, 5};
    const int arr5[] = {7};
    
    printf("arr1 is monotonic: %s\n", isMonotonic(arr1, 5) ? "true" : "false");
    printf("arr2 is monotonic: %s\n", isMonotonic(arr2, 5) ? "true" : "false");
    printf("arr3 is monotonic: %s\n", isMonotonic(arr3, 5) ? "true" : "false");
    printf("arr4 is monotonic: %s\n", isMonotonic(arr4, 5) ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'isMonotonic(arr5,1)' is always true
     *  Condition 'isMonotonic(arr5,1)' is always true [knownConditionTrueFalse]
     *  Calling function 'isMonotonic' returns 1
     */
    printf("arr5 is monotonic: %s\n", isMonotonic(arr5, 1) ? "true" : "false");
    
    /* Possible weaknesses found:
     *  Assignment 'null_zero_result=isMonotonic(NULL,0)', assigned value is 1
     *  Calling function 'isMonotonic' returns 1
     */
    bool null_zero_result = isMonotonic(NULL, 0);
    /* Possible weaknesses found:
     *  Condition 'null_zero_result' is always true
     *  Condition 'null_zero_result' is always true [knownConditionTrueFalse]
     */
    printf("NULL with size 0 is monotonic: %s\n", null_zero_result ? "true" : "false");
    
    /* Possible weaknesses found:
     *  Assignment 'null_positive_result=isMonotonic(NULL,3)', assigned value is 0
     *  Calling function 'isMonotonic' returns 0
     */
    bool null_positive_result = isMonotonic(NULL, 3);
    /* Possible weaknesses found:
     *  Condition 'null_positive_result' is always false [knownConditionTrueFalse]
     *  Condition 'null_positive_result' is always false
     */
    printf("NULL with size > 0 is monotonic: %s\n", null_positive_result ? "true" : "false");
    
    return 0;
}