#include <stdio.h>

int findKthElement(int arr[], int n, int k) {
    if (k < 0 || k >= n) {
        printf("Invalid index\n");
        return -1;
    }
    return arr[k];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;
    int result = findKthElement(arr, n, k);
    if (result != -1) {
        printf("The %dth element is %d\n", k, result);
    }
    return 0;
}