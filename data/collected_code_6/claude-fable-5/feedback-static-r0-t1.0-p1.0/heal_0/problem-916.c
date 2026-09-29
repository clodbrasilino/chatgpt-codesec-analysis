#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

bool find_triplet(int *arr, size_t n, long long target, int *out_a, int *out_b, int *out_c)
{
    size_t i;
    size_t left;
    size_t right;

    if (arr == NULL || n < 3 || out_a == NULL || out_b == NULL || out_c == NULL) {
        return false;
    }

    qsort(arr, n, sizeof(int), compare_ints);

    for (i = 0; i + 2 < n; i++) {
        left = i + 1;
        right = n - 1;

        while (left < right) {
            long long sum = (long long)arr[i] + (long long)arr[left] + (long long)arr[right];

            if (sum == target) {
                *out_a = arr[i];
                *out_b = arr[left];
                *out_c = arr[right];
                return true;
            }

            if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }

    return false;
}

int main(void)
{
    int data[] = { 12, 3, 4, 1, 6, 9 };
    size_t n = sizeof(data) / sizeof(data[0]);
    long long target = 24;
    int a = 0;
    int b = 0;
    int c = 0;

    if (find_triplet(data, n, target, &a, &b, &c)) {
        if (printf("Triplet found: %d, %d, %d\n", a, b, c) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No triplet found with sum %lld\n", target) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}