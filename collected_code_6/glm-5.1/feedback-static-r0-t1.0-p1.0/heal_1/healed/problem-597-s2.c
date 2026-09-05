#include <stdio.h>
#include <stdlib.h>

int find_kth(int *nums1, int len1, int *nums2, int len2, int k) {
    if (len1 > len2) {
        return find_kth(nums2, len2, nums1, len1, k);
    }
    if (len1 == 0) {
        if (len2 == 0 || k > len2 || k <= 0) {
            exit(EXIT_FAILURE);
        }
        return nums2[k - 1];
    }
    if (k == 1) {
        return nums1[0] < nums2[0] ? nums1[0] : nums2[0];
    }
    int half_k = k / 2;
    int partition1 = len1 < half_k ? len1 : half_k;
    int partition2 = len2 < half_k ? len2 : half_k;
    if (nums1[partition1 - 1] < nums2[partition2 - 1]) {
        return find_kth(nums1 + partition1, len1 - partition1, nums2, len2, k - partition1);
    } else {
        return find_kth(nums1, len1, nums2 + partition2, len2 - partition2, k - partition2);
    }
}

int main() {
    int nums1[] = {1, 3, 5, 7, 9};
    int nums2[] = {2, 4, 6, 8, 10};
    int len1 = sizeof(nums1) / sizeof(nums1[0]);
    int len2 = sizeof(nums2) / sizeof(nums2[0]);
    int k = 5;
    int result = find_kth(nums1, len1, nums2, len2, k);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}