#include <stdio.h>
#include <stdlib.h>

int maxBiotonic(int *arr, int n) {
    int *inc = (int *)malloc(sizeof(int) * n);
    int *dec = (int *)malloc(sizeof(int) * n);
    int max;
    int i;

    if (inc == NULL || dec == NULL) {
        if (inc != NULL) free(inc);
        if (dec != NULL) free(dec);
        return -1;
    }

    inc[0] = 1;
    dec[n - 1] = 1;

    for (i = 1; i < n; i++) {
        inc[i] = (arr[i] >= arr[i - 1]) ? inc[i - 1] + 1 : 1;
    }

    for (i = n - 2; i >= 0; i--) {
        dec[i] = (arr[i] >= arr[i + 1]) ? dec[i + 1] + 1 : 1;
    }

    max = inc[0] + dec[0] - 1;
    for (i = 1; i < n; i++) {
        if (inc[i] + dec[i] - 1 > max) {
            max = inc[i] + dec[i] - 1;
        }
    }
    free(inc);
    free(dec);
    return max;
}

int main() {
    int arr[] = {12, 4, 78, 90, 45, 23};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = maxBiotonic(arr, n);
    
    if (result != -1) {
        printf("Length of max bi-tonic series is: %d\n", result);
    } else {
        printf("Memory allocation error\n");
    }
    
    return 0;
}