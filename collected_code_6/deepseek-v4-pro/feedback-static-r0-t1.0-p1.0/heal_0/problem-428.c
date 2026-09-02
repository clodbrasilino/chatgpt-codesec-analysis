#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shell_sort(int *arr, int n) {
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = arr[i];
            j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

int main(void) {
    int arr[] = {12, 34, 54, 2, 3, 7, 8, 9, 1, 0, -4, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    shell_sort(arr, n);

    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}