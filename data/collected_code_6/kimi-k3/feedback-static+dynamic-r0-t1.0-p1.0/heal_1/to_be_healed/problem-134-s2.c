#include <stdio.h>
#include <stdlib.h>

int isLastElementEven(int arr[], int n, int p) {
    if (n <= 0 || arr == NULL) {
        return -1;
    }
    
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < n - 1; j++) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -2072745071 + -2072745074 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:18602,execs:6978,op:havoc,rep:4)
             * UBSan: signed integer overflow: 2147395601 + 92681 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:36095,execs:13057,op:havoc,rep:3)
             */
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