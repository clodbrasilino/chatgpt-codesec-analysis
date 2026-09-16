#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_kth_element(const int *arr, size_t size, size_t k, int *result)
{
    if (arr == NULL || result == NULL || size == 0 || k == 0 || k > size) {
        return -1;
    }
    *result = arr[k - 1];
    return 0;
}

int main(void)
{
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t k;
    int result;

    printf("Enter the value of k (1 to %zu): ", size);
    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (find_kth_element(arr, size, k, &result) != 0) {
        fprintf(stderr, "Invalid k value\n");
        return EXIT_FAILURE;
    }

    printf("The %zuth element is: %d\n", k, result);
    return EXIT_SUCCESS;
}