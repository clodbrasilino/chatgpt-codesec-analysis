#include <stdio.h>
#include <stdbool.h>

bool is_monotonic(const int arr[], size_t size) {
    if (size <= 1) {
        return true;
    }
    
    bool increasing = true;
    bool decreasing = true;
    
    for (size_t i = 1; i < size; i++) {
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
    
    return increasing || decreasing;
}

int main(void) {
    int arr1[] = {1, 2, 2, 3};
    int arr2[] = {6, 5, 4, 4};
    int arr3[] = {1, 3, 2};
    int arr4[] = {1};
    
    printf("Array 1 is monotonic: %s\n", is_monotonic(arr1, 4) ? "true" : "false");
    printf("Array 2 is monotonic: %s\n", is_monotonic(arr2, 4) ? "true" : "false");
    printf("Array 3 is monotonic: %s\n", is_monotonic(arr3, 3) ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'is_monotonic(arr4,1)' is always true
     *  Condition 'is_monotonic(arr4,1)' is always true [knownConditionTrueFalse]
     *  Calling function 'is_monotonic' returns 1
     */
    printf("Array 4 is monotonic: %s\n", is_monotonic(arr4, 1) ? "true" : "false");
    
    return 0;
}