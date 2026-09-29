#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void findMaxProductPair(const int arr[], int n) {
    if (n < 2) {
        printf("Array needs to have at least two elements.\n");
        return;
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
        printf("Pair with the highest product is {%d, %d}\n", max1, max2);
    } else {
        printf("Pair with the highest product is {%d, %d}\n", min1, min2);
    }
}

int main(void) {
    const int arr[] = {-10, -3, 5, 2, -100, 98, -10};
    int n = sizeof(arr) / sizeof(arr[0]);

    findMaxProductPair(arr, n);

    return 0;
}