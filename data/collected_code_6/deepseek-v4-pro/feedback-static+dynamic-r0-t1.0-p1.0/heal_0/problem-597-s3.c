#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findKthElement(int arr1[], int size1, int arr2[], int size2, int k) {
    if (k < 1 || k > size1 + size2) {
        return INT_MIN;
    }
    
    if (size2 < size1) {
        return findKthElement(arr2, size2, arr1, size1, k);
    }
    
    if (size1 == 0) {
        return arr2[k - 1];
    }
    
    if (k == 1) {
        return arr1[0] < arr2[0] ? arr1[0] : arr2[0];
    }
    
    int i = size1 < (k / 2) ? size1 : (k / 2);
    int j = k - i;
    
    if (arr1[i - 1] < arr2[j - 1]) {
        return findKthElement(arr1 + i, size1 - i, arr2, size2, k - i);
    }
    
    if (arr2[j - 1] < arr1[i - 1]) {
        return findKthElement(arr1, size1, arr2 + j, size2 - j, k - j);
    }
    
    return arr1[i - 1];
}

int main(void) {
    int arr1[] = {2, 3, 6, 7, 9};
    int arr2[] = {1, 4, 8, 10};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int k = 5;
    int result = findKthElement(arr1, size1, arr2, size2, k);
    
    if (result != INT_MIN) {
        printf("The %dth element is: %d\n", k, result);
    } else {
        printf("Invalid k value\n");
    }
    
    return 0;
}