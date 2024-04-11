#include <stdio.h>

void rearrange(int arr[], int n) {
    int i = -1;
    for (int j = 0; j < n; j++) {
        if (arr[j] < 0) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

int main() {
    int arr[] = {-12, 11, -13, -5, 6, -7, 5, -3, -6};
    int n = sizeof(arr) / sizeof(arr[0]);

    rearrange(arr, n);

    printf("Rearranged array is \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}