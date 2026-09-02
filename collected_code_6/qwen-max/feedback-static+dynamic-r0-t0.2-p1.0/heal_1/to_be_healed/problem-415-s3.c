#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
void findMaxProductPair(int arr[], int n, int *max1, int *max2) {
    if (n < 2) return;

    if (arr[0] > arr[1]) {
        *max1 = arr[0];
        *max2 = arr[1];
    } else {
        *max1 = arr[1];
        *max2 = arr[0];
    }

    for (int i = 2; i < n; i++) {
        if (arr[i] > *max1) {
            *max2 = *max1;
            *max1 = arr[i];
        } else if (arr[i] > *max2) {
            *max2 = arr[i];
        }
    }
}

int main() {
    int arr[] = {1, 4, 3, 6, 7, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max1, max2;

    findMaxProductPair(arr, n, &max1, &max2);

    if (max1 != INT_MIN && max2 != INT_MIN) {
        printf("The pair with the highest product is: %d and %d\n", max1, max2);
    } else {
        printf("Array does not have enough elements.\n");
    }

    return 0;
}