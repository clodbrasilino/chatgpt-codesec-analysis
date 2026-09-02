#include <stdio.h>
#include <stdlib.h>

int findTripletWithSum(int *arr, int n, int sum) {
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (arr[i] + arr[j] + arr[k] == sum) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    int arr[] = {1, 4, 45, 6, 10, 8};
    int sum = 22;
    int n = sizeof(arr) / sizeof(arr[0]);
    
    if (findTripletWithSum(arr, n, sum)) {
        printf("Found a triplet with the given sum\n");
    } else {
        printf("No triplet found with the given sum\n");
    }
    
    return 0;
}