#include <stdio.h>

int findKthElement(int arr[], int size, int k) {
    if (k > size) {
        return -1;
    }
    return arr[k - 1];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 5;
    int result = findKthElement(arr, size, k);
    if (result != -1) {
        printf("The %dth element is %d\n", k, result);
    } else {
        printf("Invalid input\n");
    }
    return 0;
}