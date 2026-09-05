#include <stdio.h>

long long countOddXorPairs(const int arr[], int n) {
    long long evenCount = 0;
    long long oddCount = 0;
    long long i;
    
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }
    
    return evenCount * oddCount;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("%lld\n", countOddXorPairs(arr, n));
    
    return 0;
}