#include <stdio.h>
#include <stdlib.h>

int sum_of_non_repeated_elements(int arr[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        int j;
        for(j = 0; j < n; j++) {
            if(i != j && arr[i] == arr[j]) {
                break;
            }
        }
        if(j == n) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 4, 5, 6, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = sum_of_non_repeated_elements(arr, n);
    printf("Sum of non-repeated elements is %d\n", sum);
    return 0;
}