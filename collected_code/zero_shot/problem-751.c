#include <stdio.h>
#include <stdbool.h>

bool isMinHeap(int arr[], int n) {
    for (int i = 0; i <= (n - 2) / 2; i++) {
        if (arr[i] > arr[2 * i + 1])
            return false;
        if (2 * i + 2 < n && arr[i] > arr[2 * i + 2])
            return false;
    }
    return true;
}

int main() {
    int arr[] = {2, 3, 4, 5, 10, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (isMinHeap(arr, n))
        printf("Given array represents a min heap");
    else
        printf("Given array does not represent a min heap");

    return 0;
}