#include <stdio.h>

int addMinToEvenSum(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }
    return sum % 2;
}

int main() {
    const int arr[] = {1, 3, 5, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int minAdd = addMinToEvenSum(arr, n);
    printf("Minimum number to add: %d\n", minAdd);
    return 0;
}