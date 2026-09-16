#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void findMaxProductPair(const int arr[], int n, int *first, int *second) {
    if (n < 2) {
        fprintf(stderr, "Array must contain at least two elements.\n");
        exit(EXIT_FAILURE);
    }

    int max1 = INT_MIN, max2 = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } else if (arr[i] > max2) {
            max2 = arr[i];
        }

        if (arr[i] < min1) {
            min2 = min1;
            min1 = arr[i];
        } else if (arr[i] < min2) {
            min2 = arr[i];
        }
    }

    if ((long long)max1 * max2 > (long long)min1 * min2) {
        *first = max2;
        *second = max1;
    } else {
        *first = min1;
        *second = min2;
    }
}

int main(void) {
    int arr[] = {-10, -3, 5, 6, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int num1, num2;

    findMaxProductPair(arr, n, &num1, &num2);
    printf("Pair with highest product: %d and %d\n", num1, num2);

    return 0;
}