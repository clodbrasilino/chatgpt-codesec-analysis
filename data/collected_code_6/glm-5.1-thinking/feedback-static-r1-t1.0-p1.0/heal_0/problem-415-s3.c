#include <stdio.h>
#include <limits.h>

int find_highest_product_pair(const int *arr, size_t size, int *val1, int *val2) {
    if (arr == NULL || val1 == NULL || val2 == NULL) {
        return -1;
    }

    if (size < 2) {
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

    long long prod1 = (long long)max1 * max2;
    long long prod2 = (long long)min1 * min2;

    if (prod1 >= prod2) {
        *val1 = max1;
        *val2 = max2;
    } else {
        *val1 = min1;
        *val2 = min2;
    }

    return 0;
}

int main(void) {
    int arr1[] = {1, 4, 3, 6, 2, -7, -8};
    int v1, v2;

    if (find_highest_product_pair(arr1, sizeof(arr1) / sizeof(arr1[0]), &v1, &v2) == 0) {
        printf("%d %d\n", v1, v2);
    }

    int arr2[] = {-10, -3, 5, 6, -2};
    if (find_highest_product_pair(arr2, sizeof(arr2) / sizeof(arr2[0]), &v1, &v2) == 0) {
        printf("%d %d\n", v1, v2);
    }

    int arr3[] = {5};
    if (find_highest_product_pair(arr3, sizeof(arr3) / sizeof(arr3[0]), &v1, &v2) != 0) {
        printf("Invalid input\n");
    }

    return 0;
}