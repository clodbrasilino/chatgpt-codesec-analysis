#include <stdio.h>
#include <stdbool.h>

int sumOfNonRepeated(int arr[], int n) {
    bool visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    int sum = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            bool isUnique = true;
            for (int j = i + 1; j < n; j++) {
                if (arr[i] == arr[j]) {
                    visited[j] = true;
                    isUnique = false;
                }
            }
            if (isUnique) {
                sum += arr[i];
            }
        }
    }

    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = sumOfNonRepeated(arr, n);
    printf("Sum of non-repeated elements: %d\n", result);
    return 0;
}