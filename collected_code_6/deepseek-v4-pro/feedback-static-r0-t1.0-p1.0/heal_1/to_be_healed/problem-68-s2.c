#include <stdbool.h>
#include <stddef.h>

bool isMonotonic(const int *arr, size_t size) {
    if (arr == NULL) {
        return false;
    }
    
    if (size <= 1) {
        return true;
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

#include <stdio.h>

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {5, 4, 3, 2, 1};
    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {1, 2, 2, 3, 4};
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as const array [constVariable]
     */
    int arr4[] = {1, 3, 2, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'arr5' can be declared as const array [constVariable]
     */
    int arr5[] = {7};
    /* Possible weaknesses found:
     *  Variable 'arr6' can be declared as const array [constVariable]
     */
    int arr6[] = {};
    
    printf("arr1 is monotonic: %s\n", isMonotonic(arr1, 5) ? "true" : "false");
    printf("arr2 is monotonic: %s\n", isMonotonic(arr2, 5) ? "true" : "false");
    printf("arr3 is monotonic: %s\n", isMonotonic(arr3, 5) ? "true" : "false");
    printf("arr4 is monotonic: %s\n", isMonotonic(arr4, 5) ? "true" : "false");
    printf("arr5 is monotonic: %s\n", isMonotonic(arr5, 1) ? "true" : "false");
    printf("arr6 is monotonic: %s\n", isMonotonic(arr6, 0) ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'isMonotonic(NULL,0)' is always false
     *  Condition 'isMonotonic(NULL,0)' is always false [knownConditionTrueFalse]
     *  Calling function 'isMonotonic' returns 0
     */
    printf("NULL is monotonic: %s\n", isMonotonic(NULL, 0) ? "true" : "false");
    
    return 0;
}