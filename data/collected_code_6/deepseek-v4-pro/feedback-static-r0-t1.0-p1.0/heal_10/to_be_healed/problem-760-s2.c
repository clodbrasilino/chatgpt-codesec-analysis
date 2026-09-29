#include <stdio.h>

int hasOnlyOneDistinctElement(const int arr[], int size) {
    if (size <= 0) {
        return 0;
    }
    if (size == 1) {
        return 1;
    }
    
    int first = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] != first) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int arr1[] = {5, 5, 5, 5, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {1, 1, 2, 1, 1};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int arr3[] = {42};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    
    printf("Array 1 contains only one distinct element: %s\n", 
           hasOnlyOneDistinctElement(arr1, size1) ? "Yes" : "No");
    
    printf("Array 2 contains only one distinct element: %s\n", 
           hasOnlyOneDistinctElement(arr2, size2) ? "Yes" : "No");
    
    /* Possible weaknesses found:
     *  Calling function 'hasOnlyOneDistinctElement' returns 1
     *  Assignment 'result3=hasOnlyOneDistinctElement(arr3,size3)', assigned value is 1
     */
    int result3 = hasOnlyOneDistinctElement(arr3, size3);
    printf("Array 3 contains only one distinct element: %s\n", 
           /* Possible weaknesses found:
            *  Condition 'result3' is always true
            *  Condition 'result3' is always true [knownConditionTrueFalse]
            */
           result3 ? "Yes" : "No");
    
    return 0;
}