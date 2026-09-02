#include <stdio.h>
#include <limits.h>

void find_pair_with_highest_product(const int *arr, int n, int *pair1, int *pair2) {
    if (n < 2) return;

    int max1 = INT_MIN, max2 = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;

    for (int i = 0; i < n; ++i) {
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
        *pair1 = max1;
        *pair2 = max2;
    } else {
        *pair1 = min1;
        *pair2 = min2;
    }
}

int main() {
    int arr[] = {1, 4, 3, 6, 7, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int pair1, pair2;

    find_pair_with_highest_product(arr, n, &pair1, &pair2);

    printf("Pair with the highest product: (%d, %d)\n", pair1, pair2);

    return 0;
}