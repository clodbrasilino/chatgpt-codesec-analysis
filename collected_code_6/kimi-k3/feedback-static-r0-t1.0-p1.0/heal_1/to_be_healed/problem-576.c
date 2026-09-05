#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool isSubarray(const int *subarray, size_t subSize, const int *array, size_t arraySize) {
    if (subarray == NULL || array == NULL) {
        return false;
    }
    
    if (subSize == 0) {
        return true;
    }
    
    if (subSize > arraySize) {
        return false;
    }
    
    for (size_t i = 0; i <= arraySize - subSize; i++) {
        bool found = true;
        for (size_t j = 0; j < subSize; j++) {
            if (array[i + j] != subarray[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    int array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int subarray1[] = {4, 5, 6};
    int subarray2[] = {4, 6, 8};
    int subarray3[] = {10, 11};
    /* Possible weaknesses found:
     *  Variable 'emptyArray' can be declared as const array [constVariable]
     */
    int emptyArray[] = {0};
    
    size_t arraySize = sizeof(array1) / sizeof(array1[0]);
    size_t subSize1 = sizeof(subarray1) / sizeof(subarray1[0]);
    size_t subSize2 = sizeof(subarray2) / sizeof(subarray2[0]);
    size_t subSize3 = sizeof(subarray3) / sizeof(subarray3[0]);
    
    if (isSubarray(subarray1, subSize1, array1, arraySize)) {
        printf("subarray1 is a subarray of array1\n");
    } else {
        printf("subarray1 is not a subarray of array1\n");
    }
    
    if (isSubarray(subarray2, subSize2, array1, arraySize)) {
        printf("subarray2 is a subarray of array1\n");
    } else {
        printf("subarray2 is not a subarray of array1\n");
    }
    
    if (isSubarray(subarray3, subSize3, array1, arraySize)) {
        printf("subarray3 is a subarray of array1\n");
    } else {
        printf("subarray3 is not a subarray of array1\n");
    }
    
    if (isSubarray(emptyArray, 0, array1, arraySize)) {
        printf("empty array is a subarray of array1\n");
    } else {
        printf("empty array is not a subarray of array1\n");
    }
    
    /* Possible weaknesses found:
     *  Condition 'isSubarray(NULL,5,array1,arraySize)' is always false [knownConditionTrueFalse]
     *  Calling function 'isSubarray' returns 0
     *  Condition 'isSubarray(NULL,5,array1,arraySize)' is always false
     */
    if (isSubarray(NULL, 5, array1, arraySize)) {
        printf("NULL is a subarray of array1\n");
    } else {
        printf("NULL is not a subarray of array1\n");
    }
    
    return 0;
}