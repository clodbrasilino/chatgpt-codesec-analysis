#include <stdio.h>

void findDivisible(int arr[], int size, int m, int n) {
    for(int i = 0; i < size; i++) {
        if(arr[i] % m == 0 && arr[i] % n == 0) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int size = sizeof(arr) / sizeof(arr[0]);
    int m = 2;
    int n = 4;
    findDivisible(arr, size, m, n);
    return 0;
}