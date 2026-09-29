#include <stdio.h>
#include <stddef.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int first_position(int arr[], size_t size, int target) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    size_t left = 0;
    size_t right = size;
    int found = -1;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            found = (int)mid;
            right = mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return found;
}

int main(void) {
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 5, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int targets[] = {2, 5, 7, 1, 6};
    size_t num_targets = sizeof(targets) / sizeof(targets[0]);

    for (size_t i = 0; i < num_targets; i++) {
        int pos = first_position(arr, size, targets[i]);
        printf("First position of %d: %d\n", targets[i], pos);
    }

    return 0;
}