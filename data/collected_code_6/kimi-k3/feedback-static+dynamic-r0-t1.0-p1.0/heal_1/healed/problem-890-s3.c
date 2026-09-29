#include <stdio.h>
#include <stdlib.h>

int find_extra(const int *arr1, const int *arr2, size_t n)
{
    size_t low = 0;
    size_t high = n - 1;

    if (arr1 == NULL || arr2 == NULL || n == 0) {
        return -1;
    }

    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (arr1[mid] == arr2[mid]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return (int)low;
}

int main(void)
{
    int arr1[] = {1, 2, 3, 4, 5};
    const int arr2[] = {1, 2, 3, 5};
    size_t n = sizeof(arr1) / sizeof(arr1[0]);
    int index;

    index = find_extra(arr1, arr2, n);

    if (index >= 0) {
        printf("Extra element is at index %d, value %d\n", index, arr1[index]);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}