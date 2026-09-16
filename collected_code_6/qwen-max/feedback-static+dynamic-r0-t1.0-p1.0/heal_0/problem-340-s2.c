#include <stdio.h>
#include <limits.h>

int findSumOfThreeLowest(int *arr, int n) {
    int lowest1 = INT_MAX, lowest2 = INT_MAX, lowest3 = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            if (arr[i] < lowest1) {
                lowest3 = lowest2;
                lowest2 = lowest1;
                lowest1 = arr[i];
            } else if (arr[i] < lowest2 && arr[i] != lowest1) {
                lowest3 = lowest2;
                lowest2 = arr[i];
            } else if (arr[i] < lowest3 && arr[i] != lowest2 && arr[i] != lowest1) {
                lowest3 = arr[i];
            }
        }
    }
    return (lowest1 == INT_MAX || lowest2 == INT_MAX || lowest3 == INT_MAX) ? 0 : (lowest1 + lowest2 + lowest3);
}

int main() {
    int arr[] = {5, -2, 8, 1, 9, 3, 6, 7, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = findSumOfThreeLowest(arr, n);
    printf("%d\n", sum);
    return 0;
}