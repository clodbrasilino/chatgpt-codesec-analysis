#include <stdio.h>

int findExtra(int arr1[], int arr2[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            return i;
        }
    }
    return n;
}

int main() {
    int arr1[] = {2, 4, 6, 8, 9, 10, 12};
    int arr2[] = {2, 4, 6, 8, 10, 12};
    int n = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d", findExtra(arr1, arr2, n));
    return 0;
}