#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_rotations(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return low;
        }

        int mid = low + (high - low) / 2;
        int prev = (mid - 1 + n) % n;
        int next = (mid + 1) % n;

        if (arr[mid] <= arr[prev] && arr[mid] <= arr[next]) {
            return mid;
        }

        if (arr[mid] <= arr[high]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

int main(void) {
    int arr1[] = {8, 9, 10, 2, 5, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = find_rotations(arr1, n1);
    printf("%d\n", result1);

    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = find_rotations(arr2, n2);
    printf("%d\n", result2);

    int arr3[] = {2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = find_rotations(arr3, n3);
    printf("%d\n", result3);

    int result4 = find_rotations(NULL, 5);
    printf("%d\n", result4);

    return 0;
}