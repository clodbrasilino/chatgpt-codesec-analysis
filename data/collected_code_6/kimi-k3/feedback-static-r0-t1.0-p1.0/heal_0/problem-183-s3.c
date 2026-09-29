#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static size_t count_distinct_pairs_with_diff_k(const int *arr, size_t n, int k)
{
    if (arr == NULL || n == 0 || k < 0) {
        return 0;
    }

    int *sorted = malloc(n * sizeof(int));
    if (sorted == NULL) {
        return 0;
    }

    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, n, sizeof(int), compare_ints);

    size_t count = 0;
    size_t left = 0;
    size_t right = 1;

    while (right < n) {
        long long diff = (long long)sorted[right] - (long long)sorted[left];
        
        if (diff == k) {
            count++;
            
            int current_left = sorted[left];
            int current_right = sorted[right];
            
            while (left < n && sorted[left] == current_left) {
                left++;
            }
            while (right < n && sorted[right] == current_right) {
                right++;
            }
            if (left >= right) {
                right = left + 1;
            }
        } else if (diff < k) {
            right++;
        } else {
            left++;
            if (left == right) {
                right++;
            }
        }
    }

    free(sorted);
    return count;
}

int main(void)
{
    int arr[] = {1, 5, 3, 4, 2, 5, 1, 3};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    size_t result = count_distinct_pairs_with_diff_k(arr, n, k);
    
    if (printf("Number of distinct pairs with difference %d: %zu\n", k, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}