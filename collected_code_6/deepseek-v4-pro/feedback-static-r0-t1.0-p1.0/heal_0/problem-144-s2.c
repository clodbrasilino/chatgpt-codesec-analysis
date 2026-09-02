#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

long long sum_absolute_differences(int arr[], int n) {
    if (n <= 1) {
        return 0;
    }
    
    qsort(arr, n, sizeof(int), compare_ints);
    
    long long total_sum = 0;
    long long prefix_sum = 0;
    
    for (int i = 0; i < n; i++) {
        total_sum += (long long)arr[i] * i - prefix_sum;
        prefix_sum += arr[i];
    }
    
    return total_sum;
}

int main(void) {
    int arr[] = {1, 8, 9, 15, 16};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    long long result = sum_absolute_differences(arr, n);
    printf("%lld\n", result);
    
    return 0;
}