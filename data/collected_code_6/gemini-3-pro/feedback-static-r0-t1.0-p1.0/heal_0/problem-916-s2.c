#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b) {
        return 0;
    } else if (int_a < int_b) {
        return -1;
    } else {
        return 1;
    }
}

bool findTriplet(int arr[], size_t arr_size, int sum) {
    if (arr == NULL || arr_size < 3) {
        return false;
    }

    qsort(arr, arr_size, sizeof(int), compare);

    for (size_t i = 0; i < arr_size - 2; i++) {
        size_t left = i + 1;
        size_t right = arr_size - 1;

        while (left < right) {
            int current_sum = arr[i] + arr[left] + arr[right];
            if (current_sum == sum) {
                return true;
            } else if (current_sum < sum) {
                left++;
            } else {
                right--;
            }
        }
    }

    return false;
}

int main() {
    int arr[] = {12, 3, 4, 1, 6, 9};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    int sum = 24;

    if (findTriplet(arr, arr_size, sum)) {
        printf("Triplet found\n");
    } else {
        printf("Triplet not found\n");
    }

    return EXIT_SUCCESS;
}