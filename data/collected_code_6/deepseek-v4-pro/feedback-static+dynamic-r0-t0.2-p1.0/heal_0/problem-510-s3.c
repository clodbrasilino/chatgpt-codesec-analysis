#include <stdio.h>
#include <stdlib.h>

int countSubsequencesProductLessThanK(int arr[], int n, int k) {
    if (k <= 1) return 0;
    
    int count = 0;
    int totalSubsequences = 1 << n;
    
    for (int mask = 1; mask < totalSubsequences; mask++) {
        long long product = 1;
        int valid = 1;
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (arr[i] == 0) {
                    product = 0;
                    break;
                }
                product *= arr[i];
                if (product >= k) {
                    valid = 0;
                    break;
                }
            }
        }
        
        if (valid && product < k) {
            count++;
        }
    }
    
    return count;
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 7;
    
    int result = countSubsequencesProductLessThanK(arr, n, k);
    printf("%d\n", result);
    
    int arr2[] = {4, 8, 7, 2};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 50;
    
    int result2 = countSubsequencesProductLessThanK(arr2, n2, k2);
    printf("%d\n", result2);
    
    int arr3[] = {0, 1, 2, 3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int k3 = 5;
    
    int result3 = countSubsequencesProductLessThanK(arr3, n3, k3);
    printf("%d\n", result3);
    
    return 0;
}