#include <stdio.h>

#define SIZE 100
#define CUSTOM_VALUE -1

void removeDuplicates(int arr[], int n) {
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n;) {
            if (arr[j] == arr[i]) {
                for (k = j; k < n; k++) {
                    arr[k] = arr[k + 1];
                }
                n--;
            } else {
                j++;
            }
        }
    }

    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int arr[SIZE] = {10, 20, 30, 20, 40, 50, 60, 30, 70};
    int n = 9;

    removeDuplicates(arr, n);

    return 0;
}