#include <stdio.h>
#include <stdlib.h>

int find_single_element(const int *arr, size_t n, int *result)
{
    size_t low;
    size_t high;
    size_t mid;

    if (arr == NULL || result == NULL || n == 0U || (n % 2U) == 0U) {
        return -1;
    }

    low = 0U;
    high = n - 1U;

    while (low < high) {
        mid = low + ((high - low) / 2U);
        if ((mid % 2U) == 1U) {
            mid--;
        }
        if (arr[mid] == arr[mid + 1U]) {
            low = mid + 2U;
        } else {
            high = mid;
        }
    }

    *result = arr[low];
    return 0;
}

int main(void)
{
    int arr[] = { 1, 1, 2, 2, 3, 4, 4, 5, 5 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int single = 0;

    if (find_single_element(arr, n, &single) != 0) {
        fprintf(stderr, "Invalid input array\n");
        return EXIT_FAILURE;
    }

    if (printf("The element that appears only once is: %d\n", single) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}