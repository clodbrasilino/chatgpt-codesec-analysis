#include <stdio.h>
#include <stdlib.h>

int isLastElementEven(int arr[], int n, int p) {
    if (n <= 0 || arr == NULL) {
        return -1;
    }
    
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < n - 1; j++) {
            arr[j] = arr[j] + arr[j + 1];
        }
    }
    
    return (arr[n - 1] % 2 == 0) ? 1 : 0;
}

int main() {
    int n, p;
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }
    
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    
    if (scanf("%d", &p) != 1 || p < 0) {
        free(arr);
        return 1;
    }
    
    int result = isLastElementEven(arr, n, p);
    
    if (result == 1) {
        printf("Even\n");
    } else if (result == 0) {
        printf("Odd\n");
    } else {
        printf("Error\n");
    }
    
    free(arr);
    return 0;
}