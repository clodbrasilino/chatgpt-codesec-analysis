#include <stdio.h>
#include <stdbool.h>

bool hasOneDistinctElement(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] != arr[0]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 1, 1, 1, 1};
    
    if (hasOneDistinctElement(arr1, 5)) {
        printf("arr1 contains only one distinct element\n");
    } else {
        printf("arr1 does not contain only one distinct element\n");
    }
    
    if (hasOneDistinctElement(arr2, 5)) {
        printf("arr2 contains only one distinct element\n");
    } else {
        printf("arr2 does not contain only one distinct element\n");
    }
    
    return 0;
}