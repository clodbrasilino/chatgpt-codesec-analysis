#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int count_pairs_with_diff_k(int *arr, int n, int k) {
    if (n < 2 || k < 0) {
        return 0;
    }

    qsort(arr, n, sizeof(int), cmp);

    int count = 0;
    int left = 0;
    int right = 1;

    while (right < n) {
        if (left == right) {
            right++;
            continue;
        }

        int diff = arr[right] - arr[left];

        if (diff < k) {
            right++;
        } else if (diff > k) {
            left++;
        } else {
            count++;
            int left_val = arr[left];
            int right_val = arr[right];

            while (left < n && arr[left] == left_val) {
                left++;
            }
            while (right < n && arr[right] == right_val) {
                right++;
            }
        }
    }

    return count;
}

int main() {
    int arr1[] = {1, 5, 3, 4, 2};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 3;
    int result1 = count_pairs_with_diff_k(arr1, n1, k1);
    printf("%d\n", result1);

    int arr2[] = {8, 12, 10, 10, 10, 15, 15, 20, 20};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 5;
    int result2 = count_pairs_with_diff_k(arr2, n2, k2);
    printf("%d\n", result2);

    return 0;
}