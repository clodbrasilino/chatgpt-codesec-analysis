#include <stdio.h>
#include <stdlib.h>

void extractMinMax(int* arr, int n, int k, int* minArr, int* maxArr) {
    int i, j, temp;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    for (i = 0; i < k; i++) {
        minArr[i] = arr[i];
        maxArr[i] = arr[n - i - 1];
    }
}

int main() {
    int arr[] = {7, 10, 4, 3, 20, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    int minArr[k], maxArr[k];
    int i;

    extractMinMax(arr, n, k, minArr, maxArr);

    printf("Minimum %d elements are: ", k);
    for (i = 0; i < k; i++) {
        printf("%d ", minArr[i]);
    }

    printf("\nMaximum %d elements are: ", k);
    for (i = 0; i < k; i++) {
        printf("%d ", maxArr[i]);
    }

    return 0;
}