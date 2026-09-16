#include <stdio.h>
#include <stdlib.h>

long long sumXOR(int arr[], int n) {
    long long sum = 0;
    for (int i = 0; i < 32; i++) {
        int zero_count = 0;
        int one_count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] & (1 << i)) {
                one_count++;
            } else {
                zero_count++;
            }
        }
        sum += (long long)zero_count * one_count * (1LL << i);
    }
    return sum;
}

int main(void) {
    int arr[] = {7, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    if (n <= 0) {
        return 1;
    }

    long long result = sumXOR(arr, n);
    printf("%lld\n", result);
    
    return 0;
}