#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int find_highest_product_pair(const int *arr, size_t size, int *pair1, int *pair2);

int find_highest_product_pair(const int *arr, size_t size, int *pair1, int *pair2) {
    if (arr == NULL || pair1 == NULL || pair2 == NULL || size < 2) {
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

    long long product1 = (long long)max1 * (long long)max2;
    long long product2 = (long long)min1 * (long long)min2;

    if (product1 > product2) {
        *pair1 = max1;
        *pair2 = max2;
    } else {
        *pair1 = min1;
        *pair2 = min2;
    }

    return 0;
}

int main(void) {
    const int arr[] = {-100, -98, 1, 2, 3, 4, 99};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int pair1 = 0;
    int pair2 = 0;

    int status = find_highest_product_pair(arr, size, &pair1, &pair2);
    
    if (status == 0) {
        printf("%d %d\n", pair1, pair2);
    } else {
        fprintf(stderr, "Invalid input or insufficient array elements.\n");
        return 1;
    }

    return 0;
}