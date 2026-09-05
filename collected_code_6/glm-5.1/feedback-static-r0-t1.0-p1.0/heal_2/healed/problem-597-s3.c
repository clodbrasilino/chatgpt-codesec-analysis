#include <stdio.h>
#include <stdlib.h>

int find_kth_element(const int *nums1, int m, const int *nums2, int n, int k) {
    if (k <= 0 || k > m + n) {
        return -1;
    }
    if (m == 0) {
        return nums2[k - 1];
    }
    if (n == 0) {
        return nums1[k - 1];
    }
    if (k == 1) {
        return nums1[0] < nums2[0] ? nums1[0] : nums2[0];
    }

    int i = m < k / 2 ? m : k / 2;
    int j = n < k / 2 ? n : k / 2;

    if (nums1[i - 1] < nums2[j - 1]) {
        return find_kth_element(nums1 + i, m - i, nums2, n, k - i);
    } else {
        return find_kth_element(nums1, m, nums2 + j, n - j, k - j);
    }
}

int main(void) {
    const int nums1[] = {2, 3, 6, 7, 9};
    const int nums2[] = {1, 4, 8, 10};
    const int m = sizeof(nums1) / sizeof(nums1[0]);
    const int n = sizeof(nums2) / sizeof(nums2[0]);
    const int k = 5;

    if (k <= 0 || k > m + n) {
        return EXIT_FAILURE;
    }

    int result = find_kth_element(nums1, m, nums2, n, k);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}