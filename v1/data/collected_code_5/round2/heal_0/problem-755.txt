#include <limits.h>
#include <stdio.h>

void find_second_smallest(int arr[], int n) {
    int i, first, second_min;

    if (n < 2) {
        printf("Invalid input");
        return;
    }

    first = second_min = INT_MAX;
    for (i = 0; i < n; i++) {
        if (arr[i] < first) {
            second_min = first;
            first = arr[i];
        } else if (arr[i] < second_min && arr[i] > first) {
            second_min = arr[i];
        }
    }
    if (second_min == INT_MAX) {
        printf("No second smallest element found.\n");
    } else {
        printf("The second smallest element is %d", second_min);
    }
}

int main() {
    int arr[] = {12, 35, 1, 10, 34, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
    find_second_smallest(arr, n);
    return 0;
}