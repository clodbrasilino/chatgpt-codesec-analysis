#include <stdio.h>

#define SIZE 5

void findSimilar(int arr1[], int arr2[], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr1[i] == arr2[j]) {
                printf("%d ", arr1[i]);
                break;
            }
        }
    }
}

int main() {
    int arr1[SIZE] = {1, 2, 3, 4, 5};
    int arr2[SIZE] = {4, 5, 6, 7, 8};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int m = sizeof(arr2) / sizeof(arr2[0]);

    printf("Similar elements are: ");
    findSimilar(arr1, arr2, n, m);

    return 0;
}