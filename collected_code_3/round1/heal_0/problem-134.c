#include <stdio.h>

int checkEvenOdd(int arr[], int n, int p) {
    int lastElement = arr[n-1] + p;
    if(lastElement % 2 == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int p = 3;
    int result = checkEvenOdd(arr, n, p);
    if(result == 0) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
    return 0;
}