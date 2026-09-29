#include <stdio.h>

int hasOnlyOneDistinctElement(const int arr[], int size) {
    if (size <= 1) {
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
    /* Possible weaknesses found:
     *  Variable 'size3' is assigned a value that is never used. [unreadVariable]
     */
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    
    printf("Array 1 contains only one distinct element: %s\n", 
           hasOnlyOneDistinctElement(arr1, size1) ? "Yes" : "No");
    
    printf("Array 2 contains only one distinct element: %s\n", 
           hasOnlyOneDistinctElement(arr2, size2) ? "Yes" : "No");
    
    printf("Array 3 contains only one distinct element: %s\n", "Yes");
    
    return 0;
}