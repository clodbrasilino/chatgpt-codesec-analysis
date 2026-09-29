#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm_pair(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return (a / gcd(a, b)) * b;
}

int lcm_array(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }
    
    int result = arr[0];
    for (size_t i = 1; i < size; i++) {
        result = lcm_pair(result, arr[i]);
    }
    return result;
}

int main(void) {
    int arr1[] = {2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("LCM of arr1: %d\n", lcm_array(arr1, size1));
    
    int arr2[] = {12, 15, 20};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("LCM of arr2: %d\n", lcm_array(arr2, size2));
    
    int arr3[] = {7, 11, 13};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("LCM of arr3: %d\n", lcm_array(arr3, size3));
    
    int arr4[] = {0, 5, 10};
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("LCM of arr4: %d\n", lcm_array(arr4, size4));
    
    return 0;
}