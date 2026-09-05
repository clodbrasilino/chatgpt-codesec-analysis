#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int can_be_sorted(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    int left = 0;
    int right = n - 1;

    while (left <= right) {
        if (arr[left] <= arr[left + 1]) {
            left++;
        } else if (arr[right - 1] <= arr[right]) {
            right--;
        } else {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int arr1[] = {1, 3, 5, 7, 9};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = can_be_sorted(arr1, n1);
    printf("%d\n", res1);

    int arr2[] = {9, 4, 2, 1, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = can_be_sorted(arr2, n2);
    printf("%d\n", res2);

    int arr3[] = {5, 1, 2, 3, 4};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int res3 = can_be_sorted(arr3, n3);
    printf("%d\n", res3);

    int res4 = can_be_sorted(NULL, 5);
    printf("%d\n", res4);

    return 0;
}