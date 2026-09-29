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

bool findTriplet(int arr[], int arr_size, int sum) {
    if (arr == NULL || arr_size < 3) {
        return false;
    }

    qsort(arr, arr_size, sizeof(int), compare);

    for (int i = 0; i < arr_size - 2; i++) {
        int left = i + 1;
        int right = arr_size - 1;

        while (left < right) {
            long long current_sum = (long long)arr[i] + arr[left] + arr[right];

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

int main(void) {
    int arr[] = {1, 4, 45, 6, 10, 8};
    int sum = 22;
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    if (findTriplet(arr, arr_size, sum)) {
        printf("Triplet found.\n");
    } else {
        printf("No triplet found.\n");
    }

    return 0;
}