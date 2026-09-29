#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void find_pairs(int *arr, size_t size, int target) {
    if (arr == NULL || size < 2) {
        return;
    }

    qsort(arr, size, sizeof(int), compare);

    size_t left = 0;
    size_t right = size - 1;

    while (left < right) {
        int current_sum = arr[left] + arr[right];

        if (current_sum == target) {
            printf("%d %d\n", arr[left], arr[right]);
            
            int left_val = arr[left];
            int right_val = arr[right];

            while (left < right && arr[left] == left_val) {
                left++;
            }

            while (left < right && arr[right] == right_val) {
                right--;
            }
        } else if (current_sum < target) {
            left++;
        } else {
            right--;
        }
    }
}

int main(void) {
    int arr[] = {1, 5, 7, -1, 5, 3, 3, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 6;

    find_pairs(arr, size, target);

    return 0;
}