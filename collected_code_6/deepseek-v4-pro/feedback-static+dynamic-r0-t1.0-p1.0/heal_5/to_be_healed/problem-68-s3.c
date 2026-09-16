#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool isMonotonic(const int arr[], size_t n) {
    if (n <= 2) {
        return true;
    }
    
    bool increasing = true;
    bool decreasing = true;
    
    for (size_t i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            increasing = false;
        }
        if (arr[i] > arr[i - 1]) {
            decreasing = false;
        }
        if (!increasing && !decreasing) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 2, 3, 4, 5, 6};
    int arr2[] = {6, 5, 5, 4, 3, 2, 1};
    int arr3[] = {1, 3, 2, 4, 5, 6};
    int arr4[] = {1, 1, 1, 1};
    int arr5[] = {5};
    
    bool result1 = isMonotonic(arr1, sizeof(arr1) / sizeof(arr1[0]));
    bool result2 = isMonotonic(arr2, sizeof(arr2) / sizeof(arr2[0]));
    bool result3 = isMonotonic(arr3, sizeof(arr3) / sizeof(arr3[0]));
    bool result4 = isMonotonic(arr4, sizeof(arr4) / sizeof(arr4[0]));
    /* Possible weaknesses found:
     *  Calling function 'isMonotonic' returns 1
     *  Assignment 'result5=isMonotonic(arr5,sizeof(arr5)/sizeof(arr5[0]))', assigned value is 1
     */
    bool result5 = isMonotonic(arr5, sizeof(arr5) / sizeof(arr5[0]));
    
    printf("%s\n", result1 ? "True" : "False");
    printf("%s\n", result2 ? "True" : "False");
    printf("%s\n", result3 ? "True" : "False");
    printf("%s\n", result4 ? "True" : "False");
    /* Possible weaknesses found:
     *  Condition 'result5' is always true [knownConditionTrueFalse]
     *  Condition 'result5' is always true
     */
    printf("%s\n", result5 ? "True" : "False");
    
    return 0;
}