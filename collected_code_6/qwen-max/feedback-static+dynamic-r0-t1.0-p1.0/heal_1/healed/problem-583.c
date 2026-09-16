#include <stdio.h>
#include <stdlib.h>

unsigned long long catalanNumber(int n) {
    if (n <= 1) {
        return 1;
    }
    unsigned long long* arr = (unsigned long long*)malloc((n+1) * sizeof(unsigned long long));
    if (!arr) {
        return 0;
    }
    arr[0] = arr[1] = 1;
    for (int i = 2; i <= n; i++) {
        arr[i] = 0;
        for (int j = 0; j < i; j++) {
            arr[i] += arr[j] * arr[i-j-1];
        }
    }
    unsigned long long result = arr[n];
    free(arr);
    return result;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    if (n >= 0 && n < 35) {
        unsigned long long result = catalanNumber(n);
        if (result == 0) {
            printf("Memory allocation failed.\n");
        } else {
            printf("Catalan number C(%d) is %llu\n", n, result);
        }
    } else {
        printf("Please enter a non-negative integer less than 35.\n");
    }
    return 0;
}