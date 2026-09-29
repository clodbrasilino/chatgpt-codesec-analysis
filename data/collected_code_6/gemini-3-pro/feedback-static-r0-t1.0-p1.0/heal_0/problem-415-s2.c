#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void findMaxProduct(int arr[], int n) {
    if (n < 2) {
        printf("No pairs exists\n");
        return;
    }

    if (n == 2) {
        printf("Max product pair is {%d, %d}\n", arr[0], arr[1]);
        return;
    }

    int max1 = arr[0] > arr[1] ? arr[0] : arr[1];
    int max2 = arr[0] > arr[1] ? arr[1] : arr[0];

    int min1 = arr[0] < arr[1] ? arr[0] : arr[1];
    int min2 = arr[0] < arr[1] ? arr[1] : arr[0];

    for (int i = 2; i < n; i++) {
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

    if (max1 * max2 > min1 * min2) {
        printf("Max product pair is {%d, %d}\n", max1, max2);
    } else {
        printf("Max product pair is {%d, %d}\n", min1, min2);
    }
}

int main(void) {
    int arr[] = {-1, -3, -4, 2, 0, -5};
    int n = sizeof(arr) / sizeof(arr[0]);
    findMaxProduct(arr, n);
    return 0;
}