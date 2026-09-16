#include <stdio.h>

int findUniqueElement(int arr[], int n) {
    if (n == 1) return arr[0];
    for (int i = 0; i < n; i += 2) {
        if (i + 1 == n || arr[i] != arr[i + 1]) {
            return arr[i];
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 1, 2, 2, 3, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int unique = findUniqueElement(arr, n);
    printf("The unique element is %d\n", unique);
    return 0;
}