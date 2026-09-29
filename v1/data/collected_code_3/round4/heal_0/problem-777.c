#include <stdio.h>
#include <stdlib.h>

int sumOfNonRepeated(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < n; j++)
            if (i != j && arr[i] == arr[j])
                break;
        if (j == n)
            sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Sum of non-repeated elements is %d", sumOfNonRepeated(arr, n));
    return 0;
}