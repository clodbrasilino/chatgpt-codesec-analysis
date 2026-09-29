#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool isSubarray(const int *arr, size_t n, const int *sub, size_t m)
{
    if (arr == NULL || sub == NULL) {
        return false;
    }
    if (m == 0) {
        return true;
    }
    if (m > n) {
        return false;
    }
    for (size_t i = 0; i <= n - m; i++) {
        size_t j;
        for (j = 0; j < m; j++) {
            if (arr[i + j] != sub[j]) {
                break;
            }
        }
        if (j == m) {
            return true;
        }
    }
    return false;
}

int main(void)
{
    int arr[] = {2, 3, 0, 5, 1, 1, 2};
    int sub1[] = {0, 5, 1};
    int sub2[] = {1, 5, 3};

    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t m1 = sizeof(sub1) / sizeof(sub1[0]);
    size_t m2 = sizeof(sub2) / sizeof(sub2[0]);

    if (isSubarray(arr, n, sub1, m1)) {
        printf("sub1 is a subarray of arr\n");
    } else {
        printf("sub1 is not a subarray of arr\n");
    }

    if (isSubarray(arr, n, sub2, m2)) {
        printf("sub2 is a subarray of arr\n");
    } else {
        printf("sub2 is not a subarray of arr\n");
    }

    return 0;
}