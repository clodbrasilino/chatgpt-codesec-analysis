#include <stdio.h>

void rearrange(int arr[], int n) {
    int i, j, temp;
    j = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] < 0) {
            if (i != j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            j++;
        }
    }
}

int main() {
    int arr[] = {-2, 4, -6, 8, -10, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;
    rearrange(arr, n);
    printf("Array after rearrangement: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}