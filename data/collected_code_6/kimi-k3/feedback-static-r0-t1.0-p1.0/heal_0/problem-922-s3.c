#include <stdio.h>
#include <limits.h>

int find_highest_product_pair(const int *arr, size_t size, int *first, int *second) {
    if (arr == NULL || first == NULL || second == NULL || size < 2) {
        return -1;
    }

    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int min1 = INT_MAX;
    int min2 = INT_MAX;

    for (size_t i = 0; i < size; i++) {
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

    if ((long long)max1 * max2 >= (long long)min1 * min2) {
        *first = max1;
        *second = max2;
    } else {
        *first = min1;
        *second = min2;
    }

    return 0;
}

int main(void) {
    int arr[] = {1, 10, -5, 1, -100};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int first = 0;
    int second = 0;

    if (find_highest_product_pair(arr, size, &first, &second) == 0) {
        printf("Pair: %d, %d\n", first, second);
        printf("Product: %lld\n", (long long)first * second);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}