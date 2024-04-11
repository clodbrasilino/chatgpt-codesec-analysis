#include <stdio.h>
#include <limits.h>

void sort(int arr[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min])
                min = j;
        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

int sumOfThreeSmallestNumbers(int arr[], int n) {
    sort(arr, n);
    return arr[0] + arr[1] + arr[2];
}

int main() {
    int arr[] = {12, 13, 1, 10, 34, 3};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Sum of the smallest three numbers is %d", sumOfThreeSmallestNumbers(arr, n));
    return 0;
}