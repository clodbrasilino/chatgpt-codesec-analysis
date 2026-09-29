#include <stdio.h>
#include <stdlib.h>

int find_max(const int *arr, size_t n)
{
    size_t left, right, mid;

    if (arr == NULL || n == 0) {
        return -1;
    }

    left = 0;
    right = n - 1;

    while (left < right) {
        mid = left + (right - left) / 2;

        if (arr[mid] > arr[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return arr[left];
}

int main(void)
{
    int arr[] = {4, 5, 6, 7, 1, 2, 3};
    size_t n;
    int max;

    n = sizeof(arr) / sizeof(arr[0]);
    max = find_max(arr, n);

    if (max != -1) {
        printf("%d\n", max);
    }

    return 0;
}