#include <stdio.h>

void printDuplicates(int arr[], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                printf("%d ", arr[i]);
                break;
            }
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 4, 5, 6, 7, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Duplicate elements in the list: ");
    printDuplicates(arr, n);

    return 0;
}