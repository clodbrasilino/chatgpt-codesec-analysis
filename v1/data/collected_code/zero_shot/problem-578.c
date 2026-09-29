#include <stdio.h>

void interleaveLists(int arr1[], int arr2[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr1[i]);
        printf("%d ", arr2[i]);
    }
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    interleaveLists(arr1, arr2, n);

    return 0;
}