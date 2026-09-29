#include <stdio.h>
#include <stdbool.h>

bool isMonotonic(int arr[], int n) {
    if(n==1)
        return true;

    int direction = arr[1] - arr[0];
    for (int i = 2; i < n; i++) {
        if (direction > 0 && arr[i] - arr[i - 1] < 0) {
            return false;
        }

        if (direction < 0 && arr[i] - arr[i - 1] > 0) {
            return false;
        }

        if(direction==0)
            direction= arr[i] - arr[i - 1];
    }

    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (isMonotonic(arr, n)) {
        printf("The array is monotonic\n");
    } else {
        printf("The array is not monotonic\n");
    }
    return 0;
}