#include <stdio.h>

int countRotations(const int arr[], int n) {
    int low;
    int high;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    int mid;

    if (arr == NULL || n <= 0) {
        return -1;
    }

    low = 0;
    high = n - 1;

    while (low < high) {
        mid = low + (high - low) / 2;

        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--;
        }
    }

    return low;
}

int main(void) {
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int n1 = (int)(sizeof(arr1) / sizeof(arr1[0]));
    int rotations1 = countRotations(arr1, n1);
    printf("%d\n", rotations1);

    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = (int)(sizeof(arr2) / sizeof(arr2[0]));
    int rotations2 = countRotations(arr2, n2);
    printf("%d\n", rotations2);

    int arr3[] = {2, 2, 2, 0, 2};
    int n3 = (int)(sizeof(arr3) / sizeof(arr3[0]));
    int rotations3 = countRotations(arr3, n3);
    printf("%d\n", rotations3);

    return 0;
}