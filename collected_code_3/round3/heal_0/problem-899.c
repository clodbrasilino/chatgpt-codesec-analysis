#include <stdio.h>
#include <stdbool.h>

bool check_sort(int arr[], int n) {
    int min = arr[0] < arr[n-1] ? arr[0] : arr[n-1];
    int max = arr[0] > arr[n-1] ? arr[0] : arr[n-1];

    for (int i = 1; i < n-1; i++) {
        if (arr[i] < min || arr[i] > max) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    if (check_sort(arr, n)) {
        printf("The array can be sorted by picking only the corner elements.\n");
    } else {
        printf("The array cannot be sorted by picking only the corner elements.\n");
    }

    return 0;
}