#include <stdio.h>

int countSubsequences(const int arr[], int size, int k) {
    int count = 0;
    int product = 1;
    
    for(int i = 0; i < size; i++) {
        if (arr[i] <= k) {
            count++;
            product *= arr[i];
            
            for (int j = i + 1; j < size; j++) {
                if (product * arr[j] <= k) {
                    count++;
                    product *= arr[j];
                }
            }
        }
        
        product = 1;
    }
    
    return count;
}

int main() {
    const int arr[] = {1, 2, 3, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 10;
    
    int res = countSubsequences(arr, size, k);
    
    printf("Number of subsequences having product smaller than k: %d\n", res);
    
    return 0;
}