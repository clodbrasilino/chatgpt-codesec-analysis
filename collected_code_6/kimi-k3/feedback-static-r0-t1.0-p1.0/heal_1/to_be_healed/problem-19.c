#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'nums' can be declared as pointer to const [constParameterPointer]
 */
bool containsDuplicate(int* nums, int numsSize) {
    if (nums == NULL || numsSize <= 1) {
        return false;
    }

    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] == nums[j]) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int arr[] = {1, 2, 3, 4, 2};
    int size = sizeof(arr) / sizeof(arr[0]);

    if (containsDuplicate(arr, size)) {
        printf("Array contains duplicate elements.\n");
    } else {
        printf("Array does not contain duplicate elements.\n");
    }

    return 0;
}