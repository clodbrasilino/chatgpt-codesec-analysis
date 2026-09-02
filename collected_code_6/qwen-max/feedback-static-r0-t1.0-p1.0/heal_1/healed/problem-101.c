#include <stdio.h>

int findKthElement(const int arr[], int n, int k) {
    if (k <= 0 || k > n) {
        return -1;
    }
    return arr[k-1];
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    int result = findKthElement(arr, n, k);
    if (result != -1) {
        printf("The %dth element is: %d\n", k, result);
    } else {
        printf("Invalid k value.\n");
    }

    return 0;
}