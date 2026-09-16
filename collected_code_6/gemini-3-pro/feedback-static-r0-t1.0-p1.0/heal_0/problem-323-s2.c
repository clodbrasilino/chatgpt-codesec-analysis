#include <stdio.h>
#include <stdlib.h>

void rearrange(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    int i = -1;
    for (int j = 0; j < n; j++) {
        if (arr[j] < 0) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int pos = i + 1;
    int neg = 0;

    while (pos < n && neg < pos && arr[neg] < 0) {
        int temp = arr[neg];
        arr[neg] = arr[pos];
        arr[pos] = temp;
        pos++;
        neg += 2;
    }
}

void printArray(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {-1, 2, -3, 4, 5, 6, -7, 8, -9};
    int n = sizeof(arr) / sizeof(arr[0]);

    rearrange(arr, n);
    printArray(arr, n);

    return 0;
}