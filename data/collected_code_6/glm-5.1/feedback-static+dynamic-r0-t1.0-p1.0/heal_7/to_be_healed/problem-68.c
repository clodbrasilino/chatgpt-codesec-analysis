#include <stdio.h>
#include <stdbool.h>

bool is_monotonic(const int *arr, size_t size) {
    if (size <= 2) {
        return true;
    }

    bool increasing = false;
    bool decreasing = false;

    for (size_t i = 1; i < size; i++) {
        if (arr[i] > arr[i - 1]) {
            increasing = true;
        } else if (arr[i] < arr[i - 1]) {
            decreasing = true;
        }
        
        if (increasing && decreasing) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int arr1[] = {1, 2, 2, 3, 4};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    bool res1 = is_monotonic(arr1, size1);
    printf("%s\n", res1 ? "True" : "False");

    int arr2[] = {4, 3, 2, 1};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    bool res2 = is_monotonic(arr2, size2);
    printf("%s\n", res2 ? "True" : "False");

    int arr3[] = {1, 3, 2, 4};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    bool res3 = is_monotonic(arr3, size3);
    printf("%s\n", res3 ? "True" : "False");

    int arr4[] = {5};
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    /* Possible weaknesses found:
     *  Assignment 'res4=is_monotonic(arr4,size4)', assigned value is 1
     *  Calling function 'is_monotonic' returns 1
     */
    bool res4 = is_monotonic(arr4, size4);
    /* Possible weaknesses found:
     *  Condition 'res4' is always true
     *  Condition 'res4' is always true [knownConditionTrueFalse]
     */
    printf("%s\n", res4 ? "True" : "False");

    return 0;
}