#include <stdio.h>

#define SIZE 5

void find_similar_elements(int arr1[], int arr2[], int n, int m) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
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

    printf("Similar elements are: ");
    find_similar_elements(arr1, arr2, SIZE, SIZE);

    return 0;
}