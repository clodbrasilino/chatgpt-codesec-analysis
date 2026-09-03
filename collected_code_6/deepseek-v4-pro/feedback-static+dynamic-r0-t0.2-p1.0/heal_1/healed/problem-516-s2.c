#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 10
#define MAX_DIGITS 10

int get_max(const int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void counting_sort(int *arr, int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));
    int *count = (int *)calloc(BASE, sizeof(int));
    
    if (output == NULL || count == NULL) {
        free(output);
        free(count);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % BASE]++;
    }
    
    for (int i = 1; i < BASE; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % BASE] - 1] = arr[i];
        count[(arr[i] / exp) % BASE]--;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(output);
    free(count);
}

void radix_sort(int *arr, int n) {
    if (arr == NULL || n <= 1) {
        return;
    }
    
    int max = get_max(arr, n);
    
    for (int exp = 1; max / exp > 0; exp *= BASE) {
        counting_sort(arr, n, exp);
    }
}

int main(void) {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    radix_sort(arr, n);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}