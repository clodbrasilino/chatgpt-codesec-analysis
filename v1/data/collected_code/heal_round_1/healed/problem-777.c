#include <stdbool.h>
#include <stdio.h>

int sumNonRepeatedElements(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        bool repeated = false;
        for (int j = 0; j < n; j++) {
            if (i != j && arr[i] == arr[j]) {
                repeated = true;
                break;
            }
        }
        if (!repeated) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Sum of non-repeated elements is %d\n", sumNonRepeatedElements(arr, n));

    return 0;
}