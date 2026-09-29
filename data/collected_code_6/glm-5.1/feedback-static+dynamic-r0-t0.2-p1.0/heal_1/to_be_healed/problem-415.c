#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void find_max_product_pair(int *arr, int size, int *max1, int *max2) {
    if (arr == NULL || size < 2 || max1 == NULL || max2 == NULL) {
        exit(EXIT_FAILURE);
    }

    int max_a = INT_MIN;
    int max_b = INT_MIN;
    int min_a = INT_MAX;
    int min_b = INT_MAX;

    for (int i = 0; i < size; i++) {
        if (arr[i] > max_a) {
            max_b = max_a;
            max_a = arr[i];
        } else if (arr[i] > max_b) {
            max_b = arr[i];
        }

        if (arr[i] < min_a) {
            min_b = min_a;
            min_a = arr[i];
        } else if (arr[i] < min_b) {
            min_b = arr[i];
        }
    }

    long long product_max = (long long)max_a * max_b;
    long long product_min = (long long)min_a * min_b;

    if (product_max > product_min) {
        *max1 = max_a;
        *max2 = max_b;
    } else {
        *max1 = min_a;
        *max2 = min_b;
    }
}

int main(void) {
    int arr[] = {1, -4, 3, -6, 7, 0};
    int size = sizeof(arr) / sizeof(arr[0]);
    int val1, val2;

    find_max_product_pair(arr, size, &val1, &val2);

    printf("Pair with highest product: %d and %d\n", val1, val2);
    printf("Highest product: %lld\n", (long long)val1 * val2);

    return 0;
}