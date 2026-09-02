#include <stdio.h>
#include <stdlib.h>

void rearrange(int *arr, int n) {
    int pos = 0, neg = 1;
    int temp[n];
    
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= 0 && pos < n) {
            temp[pos] = arr[i];
            pos += 2;
        } else if (arr[i] < 0 && neg < n) {
            temp[neg] = arr[i];
            neg += 2;
        }
    }

    if (pos < n)
        pos = 0;
    else
        neg = 1;

    for (int i = 0; i < n; ++i) {
        if (arr[i] < 0 && pos < n) {
            temp[pos] = arr[i];
            pos += 2;
        } else if (arr[i] >= 0 && neg < n) {
            temp[neg] = arr[i];
            neg += 2;
        }
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = temp[i];
    }
}

int main() {
    int arr[] = {9, 4, -2, -1, 5, 0, -5};
    int n = sizeof(arr) / sizeof(arr[0]);

    rearrange(arr, n);

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}