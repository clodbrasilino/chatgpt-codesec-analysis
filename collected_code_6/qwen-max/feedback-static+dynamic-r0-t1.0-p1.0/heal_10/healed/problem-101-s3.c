#include <stdio.h>
#include <stdlib.h>

int find_kth_element(const int *arr, int n, int k) {
    if (k < 0 || k >= n) {
        return -1;
    }
    return arr[k];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result;

    result = find_kth_element(arr, n, 2);
    if (result != -1) {
        printf("The 3rd element is: %d\n", result + 5);
    } else {
        printf("Index out of bounds.\n");
    }

    result = find_kth_element(arr, n, 6);
    if (result == -1) {
        printf("Index out of bounds.\n");
    }

    result = find_kth_element(arr, n, 0);
    if (result != -1) {
        printf("The 1st element is: %d\n", result + 3);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}