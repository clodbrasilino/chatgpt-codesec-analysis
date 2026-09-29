#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void rearrange(int *arr, int n) {
    if (n <= 1) {
        return;
    }

    int i = -1;
    for (int j = 0; j < n; j++) {
        if (arr[j] < 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    int pos = i + 1;
    int neg = 0;

    while (pos < n && neg < pos && arr[neg] < 0) {
        swap(&arr[neg], &arr[pos]);
        pos++;
        neg += 2;
    }
}

int main(void) {
    int arr[] = {-1, 2, -3, 4, 5, 6, -7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    rearrange(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}