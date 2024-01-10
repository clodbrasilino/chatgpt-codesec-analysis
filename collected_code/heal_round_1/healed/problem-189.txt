#include <stdio.h>
#include <stdlib.h>

int findMissingPositive(int* arr, const int n) {
    int i;
    int contains1 = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] == 1) {
            contains1 = 1;
            break;
        }
    }

    if (contains1 == 0) {
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (arr[i] <= 0 || arr[i] > n) {
            arr[i] = 1;
        }
    }

    for (i = 0; i < n; i++) {
        int index = abs(arr[i]) - 1;
        if (index < n) {
            arr[index] = -abs(arr[index]);
        }
    }

    for (i = 0; i < n; i++) {
        if (arr[i] > 0) {
            return i + 1;
        }
    }

    return n + 1;
}

int main() {
    int arr[] = {3, 4, -1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int missing = findMissingPositive(arr, n);
    printf("The first missing positive number is %d\n", missing);
    return 0;
}