#include <stdio.h>
#include <stdlib.h>

int find_kth_element(int arr[], int size, int k) {
    if (k < 1 || k > size) {
        return -1;
    }
    return arr[k - 1];
}

int main() {
    int n, k, result;
    int *arr;
    int i;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for array size.\n");
        return 1;
    }

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input for array element.\n");
            free(arr);
            return 1;
        }
    }

    printf("Enter k (1-based index): ");
    if (scanf("%d", &k) != 1) {
        printf("Invalid input for k.\n");
        free(arr);
        return 1;
    }

    result = find_kth_element(arr, n, k);
    if (result == -1) {
        printf("Invalid value of k.\n");
    } else {
        printf("The %dth element is: %d\n", k, result);
    }

    free(arr);
    return 0;
}