#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

bool same_inversion_counts(const int *arr, size_t n)
{
    long long mx;
    size_t j;

    if (arr == NULL || n == 0U) {
        return true;
    }

    mx = LLONG_MIN;
    for (j = 1U; j < n; j++) {
        if (mx > (long long)arr[j]) {
            return false;
        }
        if ((long long)arr[j - 1U] > mx) {
            mx = (long long)arr[j - 1U];
        }
    }
    return true;
}

int main(void)
{
    int arr1[] = {1, 0, 2};
    int arr2[] = {1, 2, 0};
    int arr3[] = {1, 2, 1};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    int rc;

    rc = printf("%s\n", same_inversion_counts(arr1, n1) ? "True" : "False");
    if (rc < 0) {
        return 1;
    }
    rc = printf("%s\n", same_inversion_counts(arr2, n2) ? "True" : "False");
    if (rc < 0) {
        return 1;
    }
    rc = printf("%s\n", same_inversion_counts(arr3, n3) ? "True" : "False");
    if (rc < 0) {
        return 1;
    }

    return 0;
}