#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr2' can be declared as pointer to const [constParameterPointer]
 */
int isSubset(int *arr1, int size1, int *arr2, int size2) {
    if (arr1 == NULL || arr2 == NULL) return 0;
    if (size1 < 0 || size2 < 0) return 0;
    
    for (int i = 0; i < size2; i++) {
        int found = 0;
        for (int j = 0; j < size1; j++) {
            if (arr1[j] == arr2[i]) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int main() {
    int arr1[] = {11, 1, 13, 21, 3, 7};
    int arr2[] = {11, 3, 7, 1};
    
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    if (isSubset(arr1, size1, arr2, size2)) {
        printf("arr2 is a subset of arr1\n");
    } else {
        printf("arr2 is not a subset of arr1\n");
    }
    
    int arr3[] = {1, 2, 3, 4, 5, 6};
    int arr4[] = {1, 2, 4};
    
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    
    if (isSubset(arr3, size3, arr4, size4)) {
        printf("arr4 is a subset of arr3\n");
    } else {
        printf("arr4 is not a subset of arr3\n");
    }
    
    int arr5[] = {10, 5, 2, 23, 19};
    int arr6[] = {19, 5, 3};
    
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    int size6 = sizeof(arr6) / sizeof(arr6[0]);
    
    if (isSubset(arr5, size5, arr6, size6)) {
        printf("arr6 is a subset of arr5\n");
    } else {
        printf("arr6 is not a subset of arr5\n");
    }
    
    return 0;
}