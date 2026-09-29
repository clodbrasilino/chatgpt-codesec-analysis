#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define RADIX 10

void getMax(const int arr[], int n, int *max) {
    *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int count[RADIX] = {0};

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % RADIX]++;
    }

    for (int i = 1; i < RADIX; i++) {
        count[i] += count[i - 1];
    }

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % RADIX] - 1] = arr[i];
        count[(arr[i] / exp) % RADIX]--;
    }

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Uninitialized variable: output [uninitvar]
         *  Uninitialized variable: output
         */
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n) {
    int max;
    getMax(arr, n, &max);

    for (int exp = 1; max / exp > 0; exp *= RADIX) {
        countSort(arr, n, exp);
    }
}

int main() {
    int arr[MAX], n, i;

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX) {
        return 1;
    }

    printf("Enter the elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    radixSort(arr, n);

    printf("Sorted list: \n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}