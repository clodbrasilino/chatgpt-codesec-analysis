#include <stdio.h>
#include <stdlib.h>

int qsort_cmp(const void *a, const void *b) {
    long long va = *(const int *)a;
    long long vb = *(const int *)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int findTriplet(int *arr, int n, int target) {
    if (n < 3) {
        return 0;
    }
    qsort(arr, n, sizeof(int), qsort_cmp);
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) {
            continue;
        }
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            long long sum = (long long)arr[i] + arr[left] + arr[right];
            if (sum == target) {
                return 1;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    return 0;
}

int main() {
    int arr1[] = {1, 4, 45, 6, 10, 8};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int target1 = 22;
    int result1 = findTriplet(arr1, n1, target1);
    printf("%d\n", result1);

    int arr2[] = {1, 2, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int target2 = 6;
    int result2 = findTriplet(arr2, n2, target2);
    printf("%d\n", result2);

    int arr3[] = {10, 20, 30};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int target3 = 100;
    int result3 = findTriplet(arr3, n3, target3);
    printf("%d\n", result3);

    return 0;
}