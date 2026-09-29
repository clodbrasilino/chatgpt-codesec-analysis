#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    long long diff = *(long long *)a - *(long long *)b;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

int count_pairs_with_diff_k(const int *arr, int n, int k) {
    if (n < 2 || k < 0) {
        return 0;
    }

    long long *larr = (long long *)malloc(n * sizeof(long long));
    if (!larr) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        larr[i] = arr[i];
    }

    qsort(larr, n, sizeof(long long), cmp);

    int count = 0;
    int left = 0;
    int right = 0;

    while (right < n) {
        long long diff = larr[right] - larr[left];
        
        if (diff < k) {
            right++;
        } else if (diff > k) {
            left++;
        } else {
            long long val_r = larr[right];
            long long val_l = larr[left];
            
            long long count_r = 0;
            while (right < n && larr[right] == val_r) {
                right++;
                count_r++;
            }
            
            long long count_l = 0;
            while (left < n && larr[left] == val_l) {
                left++;
                count_l++;
            }
            
            if (val_l == val_r) {
                count += (count_r * (count_r - 1)) / 2;
            } else {
                count += count_l * count_r;
            }
        }
        
        if (left == right) {
            right++;
        }
    }

    free(larr);
    return count;
}

int main() {
    int arr1[] = {1, 5, 3, 4, 2};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 3;
    printf("%d\n", count_pairs_with_diff_k(arr1, n1, k1));

    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 1;
    printf("%d\n", count_pairs_with_diff_k(arr2, n2, k2));

    int arr3[] = {1, 1, 1, 2, 2};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int k3 = 0;
    printf("%d\n", count_pairs_with_diff_k(arr3, n3, k3));

    int arr4[] = {1, 3, 5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int k4 = -1;
    printf("%d\n", count_pairs_with_diff_k(arr4, n4, k4));

    int arr5[] = {1};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    int k5 = 1;
    printf("%d\n", count_pairs_with_diff_k(arr5, n5, k5));

    return 0;
}