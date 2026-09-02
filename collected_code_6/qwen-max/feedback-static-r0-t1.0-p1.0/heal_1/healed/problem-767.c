#include <stdio.h>
#include <stdlib.h>

int count_pairs_with_sum(const int *arr, int n, int sum) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] + arr[j] == sum) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 10;
    int result = count_pairs_with_sum(arr, n, sum);
    printf("Number of pairs with sum %d: %d\n", sum, result);
    return 0;
}