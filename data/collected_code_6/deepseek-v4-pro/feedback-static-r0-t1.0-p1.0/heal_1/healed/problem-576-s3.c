#include <stdio.h>
#include <stdlib.h>

int is_subarray(const int *a, int len_a, const int *b, int len_b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (len_a < 0 || len_b < 0) {
        return 0;
    }
    if (len_b > len_a) {
        return 0;
    }
    if (len_b == 0) {
        return 1;
    }
    
    for (int i = 0; i <= len_a - len_b; i++) {
        int j;
        for (j = 0; j < len_b; j++) {
            if (a[i + j] != b[j]) {
                break;
            }
        }
        if (j == len_b) {
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5, 6};
    int arr2[] = {3, 4, 5};
    int arr3[] = {3, 5, 4};
    int arr4[] = {7, 8};
    int arr5[] = {};
    int arr6[] = {1, 2, 3, 4, 5, 6};
    
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    int len3 = sizeof(arr3) / sizeof(arr3[0]);
    int len4 = sizeof(arr4) / sizeof(arr4[0]);
    int len5 = sizeof(arr5) / sizeof(arr5[0]);
    int len6 = sizeof(arr6) / sizeof(arr6[0]);
    
    printf("%d\n", is_subarray(arr1, len1, arr2, len2));
    printf("%d\n", is_subarray(arr1, len1, arr3, len3));
    printf("%d\n", is_subarray(arr1, len1, arr4, len4));
    printf("%d\n", is_subarray(arr1, len1, arr5, len5));
    printf("%d\n", is_subarray(arr1, len1, arr6, len6));
    printf("%d\n", is_subarray(NULL, 5, arr2, len2));
    printf("%d\n", is_subarray(arr1, -1, arr2, len2));
    
    return 0;
}