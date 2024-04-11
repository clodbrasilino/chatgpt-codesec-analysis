#include <stdio.h>
#include <stdlib.h>

int convertToInt(int* arr, int n) {
    int result = 0;
    for(int i = 0; i < n; i++) {
        result = result * 10 + arr[i];
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = convertToInt(arr, n);
    printf("%d\n", result);
    return 0;
}