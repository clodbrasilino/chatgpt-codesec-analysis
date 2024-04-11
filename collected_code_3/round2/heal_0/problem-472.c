#include <stdio.h>
#include <stdbool.h>

bool areConsecutive(int arr[], int n) {
    int min = arr[0];
    int sum = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min)
            min = arr[i];
        sum += arr[i];
    }
    int total = n * (min + (min + n - 1)) / 2;
    return sum == total;
}

int main() {
    int arr[] = {5, 2, 3, 1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (areConsecutive(arr, n) == true)
        printf("Array elements are consecutive\n");
    else
        printf("Array elements are not consecutive\n");
    return 0;
}