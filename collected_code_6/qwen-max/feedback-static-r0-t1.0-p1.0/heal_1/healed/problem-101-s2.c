#include <stdio.h>
#include <stdbool.h>

int findKthElement(const int arr[], int size, int k) {
    if (k <= 0 || k > size) {
        return -1;
    }
    return arr[k - 1];
}

int main() {
    int arr[] = {3, 7, 4, 2, 8, 16, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 5;

    int result = findKthElement(arr, size, k);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid k value\n");
    }

    return 0;
}