#include <stdio.h>

float findDivision(int arr[], int n) {
    int i, even = -1, odd = -1;
    for(i = 0; i < n; i++) {
        if(arr[i] % 2 == 0 && even == -1) {
            even = arr[i];
        }
        if(arr[i] % 2 != 0 && odd == -1) {
            odd = arr[i];
        }
        if(even != -1 && odd != -1) {
            break;
        }
    }
    if(even != -1 && odd != -1) {
        return (float)even / odd;
    } else {
        return -1;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    float result = findDivision(arr, n);
    if(result != -1) {
        printf("Division of first even and odd number is %.2f\n", result);
    } else {
        printf("No even and odd number found in the list\n");
    }
    return 0;
}