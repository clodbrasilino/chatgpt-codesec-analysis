#include <stdio.h>

int countOdd(int* arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int oddCount = countOdd(arr, n);

    printf("Number of odd elements in the array: %d\n", oddCount);

    return 0;
}