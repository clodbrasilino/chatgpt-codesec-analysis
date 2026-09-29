#include<stdio.h>

void removeDuplicates(const int arr[], int n) {
    if (n == 0 || n == 1) {
        return;
    }

    int temp[n];
    int j = 0;

    for (int i = 0; i < n-1; i++) {
        if (arr[i] != arr[i+1]) {
            temp[j++] = arr[i];
        }
    }

    temp[j++] = arr[n-1];

    for (int i = 0; i < j; i++) {
        arr[i] = temp[i];
    }

    printf("The modified list after removing consecutive duplicates is: \n");
    for (int i = 0; i < j; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int arr[] = {10, 20, 20, 30, 40, 40, 40, 50, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    removeDuplicates(arr, n);

    return 0;
}