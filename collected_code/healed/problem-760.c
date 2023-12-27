#include <stdio.h>
#include <stdbool.h>

bool hasOneDistinctElement(const int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[0]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 1, 1, 1, 1};
    
    if (hasOneDistinctElement(arr1, sizeof(arr1)/sizeof(arr1[0]))) {
        printf("arr1 contains only one distinct element\n");
    } else {
        printf("arr1 does not contain only one distinct element\n");
    }
    
    if (hasOneDistinctElement(arr2, sizeof(arr2)/sizeof(arr2[0]))) {
        printf("arr2 contains only one distinct element\n");
    } else {
        printf("arr2 does not contain only one distinct element\n");
    }
    
    return 0;
}