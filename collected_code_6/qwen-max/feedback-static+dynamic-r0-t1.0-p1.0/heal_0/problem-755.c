#include <stdio.h>
#include <limits.h>

int second_smallest(int *arr, int n) {
    int smallest = INT_MAX;
    int ssmallest = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] < smallest) {
            ssmallest = smallest;
            smallest = arr[i];
        } else if (arr[i] < ssmallest && arr[i] != smallest) {
            ssmallest = arr[i];
        }
    }
    return (ssmallest == INT_MAX || smallest == ssmallest) ? -1 : ssmallest;
}

int main() {
    int arr[] = {9, 2, 7, 3, 5, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int res = second_smallest(arr, n);
    if (res == -1) {
        printf("There is no second smallest element.\n");
    } else {
        printf("Second smallest element is %d\n", res);
    }
    return 0;
}