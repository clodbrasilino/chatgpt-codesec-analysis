#include <stdio.h>
#include <limits.h>

int secondSmallest(int arr[], int n) {
    int first, second;
    first = second = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] < first) {
            second = first;
            first = arr[i];
        } else if (arr[i] < second && arr[i] != first)
            second = arr[i];
    }

    if (second == INT_MAX)
        return INT_MAX;
    else
        return second;
}

int main() {
    int arr[] = {12, 13, 1, 10, 34, 2};
    int n = sizeof(arr)/sizeof(arr[0]);
    int second = secondSmallest(arr, n);
    if (second == INT_MAX)
        printf("No second smallest element\n");
    else
        printf("The second smallest element is %d\n", second);
    return 0;
}