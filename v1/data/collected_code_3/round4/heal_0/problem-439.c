#include <stdio.h>
#include <stdlib.h>

int convertToInt(int *arr, int n) {
    int num = 0;
    for(int i = 0; i < n; i++) {
        int temp = arr[i];
        while(temp > 0) {
            num = num * 10 + temp % 10;
            temp = temp / 10;
        }
    }
    return num;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int num = convertToInt(arr, n);
    printf("%d\n", num);
    return 0;
}