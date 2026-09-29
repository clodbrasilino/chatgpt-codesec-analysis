#include <stdio.h>
#include <stdlib.h>

int sumOfRepeated(int arr[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] == arr[j]) {
                sum += arr[i];
                break;
            }
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 4, 5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = sumOfRepeated(arr, n);
    printf("Sum of repeated elements is %d\n", sum);
    return 0;
}