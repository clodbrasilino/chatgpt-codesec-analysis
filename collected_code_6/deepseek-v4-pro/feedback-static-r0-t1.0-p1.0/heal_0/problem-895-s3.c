#include <stdio.h>
#include <stdlib.h>

int max_sum_no_adjacent(int *arr, int size) {
    if (size <= 0) {
        return 0;
    }
    
    if (size == 1) {
        return arr[0] > 0 ? arr[0] : 0;
    }
    
    int incl = arr[0];
    int excl = 0;
    int excl_new;
    
    for (int i = 1; i < size; i++) {
        excl_new = incl > excl ? incl : excl;
        incl = excl + arr[i];
        excl = excl_new;
    }
    
    return incl > excl ? incl : excl;
}

int main(void) {
    int arr1[] = {5, 5, 10, 100, 10, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Maximum sum: %d\n", max_sum_no_adjacent(arr1, size1));
    
    int arr2[] = {1, 2, 3};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Maximum sum: %d\n", max_sum_no_adjacent(arr2, size2));
    
    int arr3[] = {5, -5, 10, -1, 2, -3};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Maximum sum: %d\n", max_sum_no_adjacent(arr3, size3));
    
    int arr4[] = {-2, -1, -3, -4, -5};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("Maximum sum: %d\n", max_sum_no_adjacent(arr4, size4));
    
    int arr5[] = {10};
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("Maximum sum: %d\n", max_sum_no_adjacent(arr5, size5));
    
    return 0;
}