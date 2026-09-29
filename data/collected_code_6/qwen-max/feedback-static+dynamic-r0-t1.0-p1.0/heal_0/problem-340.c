#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int sumOfThreeLowestPositive(int *arr, int n) {
    qsort(arr, n, sizeof(int), compare);
    int sum = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            sum += arr[i];
            count++;
            if (count == 3) {
                break;
            }
        }
    }
    return (count == 3) ? sum : -1;
}

int main() {
    int arr[] = {5, -2, 0, 3, 1, 4, -1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = sumOfThreeLowestPositive(arr, n);
    if (result != -1) {
        printf("Sum of the three lowest positive numbers: %d\n", result);
    } else {
        printf("Less than three positive numbers in the list.\n");
    }
    return 0;
}