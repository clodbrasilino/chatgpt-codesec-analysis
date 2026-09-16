#include <stdio.h>

int count_odd_xor_pairs(const int arr[], int n) {
    if (arr == NULL || n <= 1) {
        return 0;
    }
    
    int even_count = 0;
    int odd_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }
    
    return even_count * odd_count;
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {2, 4, 6, 8};
    int arr3[] = {1, 3, 5};
    int arr4[] = {5};
    int arr5[] = {};
    
    printf("%d\n", count_odd_xor_pairs(arr1, 3));
    printf("%d\n", count_odd_xor_pairs(arr2, 4));
    printf("%d\n", count_odd_xor_pairs(arr3, 3));
    printf("%d\n", count_odd_xor_pairs(arr4, 1));
    printf("%d\n", count_odd_xor_pairs(arr5, 0));
    printf("%d\n", count_odd_xor_pairs(NULL, 5));
    
    return 0;
}