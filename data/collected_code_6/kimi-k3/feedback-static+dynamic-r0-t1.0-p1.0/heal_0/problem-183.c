#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

size_t count_pairs_with_difference_k(int arr[], size_t n, int k)
{
    if (arr == NULL || n < 2 || k < 0) {
        return 0;
    }

    qsort(arr, n, sizeof(int), compare_ints);

    size_t count = 0;
    size_t i = 0;
    size_t j = 1;

    while (j < n) {
        long diff = (long)arr[j] - (long)arr[i];

        if (diff == k) {
            count++;
            i++;
            j++;
            while (i < n && arr[i] == arr[i - 1]) {
                i++;
            }
            while (j < n && arr[j] == arr[j - 1]) {
                j++;
            }
            if (i >= j) {
                j = i + 1;
            }
        } else if (diff < k) {
            j++;
        } else {
            i++;
            if (i == j) {
                j++;
            }
        }
    }

    return count;
}

int main(void)
{
    int arr[] = {1, 5, 3, 4, 2};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    size_t result = count_pairs_with_difference_k(arr, n, k);
    printf("Number of distinct pairs with difference %d: %zu\n", k, result);

    return 0;
}