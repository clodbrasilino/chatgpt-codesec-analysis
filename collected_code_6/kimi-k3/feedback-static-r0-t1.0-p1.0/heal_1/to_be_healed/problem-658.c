#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findMaxOccurrence(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int maxCount = 0;
    int maxItem = arr[0];

    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            maxItem = arr[i];
        }
    }

    return maxItem;
}

int main(void) {
    int arr[] = {1, 3, 2, 3, 4, 3, 2, 1, 3};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = findMaxOccurrence(arr, size);

    if (result != -1) {
        printf("Item with maximum occurrences: %d\n", result);
    } else {
        printf("Invalid input or empty array.\n");
    }

    return 0;
}