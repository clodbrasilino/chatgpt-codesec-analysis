#include <stdio.h>
#include <stdbool.h>

bool areArraysEqual(const int *arr1, size_t size1, const int *arr2, size_t size2) {
    if (arr1 == NULL || arr2 == NULL) {
        return arr1 == NULL && arr2 == NULL;
    }
    
    if (size1 != size2) {
        return false;
    }
    
    if (arr1 == arr2) {
        return true;
    }
    
    for (size_t i = 0; i < size1; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {1, 2, 3, 4, 6};
    int arr4[] = {1, 2, 3, 4, 5, 6};
    
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    
    if (areArraysEqual(arr1, size1, arr2, size2)) {
        printf("arr1 and arr2 are equal\n");
    } else {
        printf("arr1 and arr2 are not equal\n");
    }
    
    if (areArraysEqual(arr1, size1, arr3, size3)) {
        printf("arr1 and arr3 are equal\n");
    } else {
        printf("arr1 and arr3 are not equal\n");
    }
    
    if (areArraysEqual(arr1, size1, arr4, size4)) {
        printf("arr1 and arr4 are equal\n");
    } else {
        printf("arr1 and arr4 are not equal\n");
    }
    
    /* Possible weaknesses found:
     *  Condition 'areArraysEqual(NULL,0,NULL,0)' is always true
     *  Condition 'areArraysEqual(NULL,0,NULL,0)' is always true [knownConditionTrueFalse]
     *  Calling function 'areArraysEqual' returns 1
     */
    if (areArraysEqual(NULL, 0, NULL, 0)) {
        printf("NULL arrays are equal\n");
    } else {
        printf("NULL arrays are not equal\n");
    }
    
    return 0;
}