#include <stdio.h>
#include <stdlib.h>

int countUnequalPairs(int *arr, int n) {
    if (arr == NULL || n < 0) {
        return -1;
    }
    if (n < 2) {
        return 0;
    }
    
    int totalPairs = n * (n - 1) / 2;
    int equalPairs = 0;
    
    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] == arr[i]) {
                count++;
            }
        }
        if (count > 1) {
            int seen = 0;
            for (int k = 0; k < i; k++) {
                if (arr[k] == arr[i]) {
                    seen = 1;
                    break;
                }
            }
            if (!seen) {
                equalPairs += count * (count - 1) / 2;
            }
        }
    }
    
    return totalPairs - equalPairs;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = countUnequalPairs(arr1, n1);
    printf("%d\n", result1);
    
    int arr2[] = {1, 1, 1, 2, 2};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = countUnequalPairs(arr2, n2);
    printf("%d\n", result2);
    
    int arr3[] = {5, 5, 5, 5, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = countUnequalPairs(arr3, n3);
    printf("%d\n", result3);
    
    int *arr4 = NULL;
    int result4 = countUnequalPairs(arr4, 0);
    printf("%d\n", result4);
    
    int arr5[] = {42};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    int result5 = countUnequalPairs(arr5, n5);
    printf("%d\n", result5);
    
    return 0;
}