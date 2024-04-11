#include <stdio.h>
#include <stdlib.h>

int countPairsWithDiffK(int arr[], int n, int k) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] - arr[j] == k || arr[j] - arr[i] == k) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 5, 3, 4, 2};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 3;
    printf("Count of pairs with given diff is %d\n", countPairsWithDiffK(arr, n, k));
    return 0;
}