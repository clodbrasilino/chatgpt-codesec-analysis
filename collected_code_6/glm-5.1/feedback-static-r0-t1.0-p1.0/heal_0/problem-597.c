#include <stdio.h>
#include <stdlib.h>

int find_kth_element(int *nums1, int m, int *nums2, int n, int k) {
    if (nums1 == NULL) m = 0;
    if (nums2 == NULL) n = 0;
    if (k <= 0 || k > m + n) return -1;

    int index1 = 0, index2 = 0;
    while (1) {
        if (index1 == m) return nums2[index2 + k - 1];
        if (index2 == n) return nums1[index1 + k - 1];
        if (k == 1) return nums1[index1] < nums2[index2] ? nums1[index1] : nums2[index2];

        int half = k / 2;
        int new_index1 = index1 + half - 1 < m - 1 ? index1 + half - 1 : m - 1;
        int new_index2 = index2 + half - 1 < n - 1 ? index2 + half - 1 : n - 1;

        if (nums1[new_index1] <= nums2[new_index2]) {
            k -= (new_index1 - index1 + 1);
            index1 = new_index1 + 1;
        } else {
            k -= (new_index2 - index2 + 1);
            index2 = new_index2 + 1;
        }
    }
}

int main() {
    int arr1[] = {2, 3, 6, 7, 9};
    int arr2[] = {1, 4, 8, 10};
    int m = sizeof(arr1) / sizeof(arr1[0]);
    int n = sizeof(arr2) / sizeof(arr2[0]);
    int k = 5;

    int result = find_kth_element(arr1, m, arr2, n, k);

    printf("%d\n", result);

    return 0;
}