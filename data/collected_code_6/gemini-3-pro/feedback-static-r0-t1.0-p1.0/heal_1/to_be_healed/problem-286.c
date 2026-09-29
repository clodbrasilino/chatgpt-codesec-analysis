#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
long long int maxSubArraySum(int arr[], int n, int k) {
    if (arr == NULL || n <= 0 || k <= 0) {
        return 0;
    }

    long long int max_so_far = arr[0];
    long long int curr_max = arr[0];
    long long int total_sum = arr[0];

    for (int i = 1; i < n; i++) {
        total_sum += arr[i];
        
        if (curr_max > 0) {
            curr_max += arr[i];
        } else {
            curr_max = arr[i];
        }
        
        if (curr_max > max_so_far) {
            max_so_far = curr_max;
        }
    }

    if (k == 1) {
        return max_so_far;
    }

    long long int prefix_sum = arr[0];
    long long int max_prefix_sum = arr[0];
    for (int i = 1; i < n; i++) {
        prefix_sum += arr[i];
        if (prefix_sum > max_prefix_sum) {
            max_prefix_sum = prefix_sum;
        }
    }

    long long int suffix_sum = arr[n - 1];
    long long int max_suffix_sum = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        suffix_sum += arr[i];
        if (suffix_sum > max_suffix_sum) {
            max_suffix_sum = suffix_sum;
        }
    }

    long long int result = max_so_far;

    if (total_sum > 0) {
        long long int extended_sum = max_prefix_sum + max_suffix_sum + (total_sum * (k - 2));
        if (extended_sum > result) {
            result = extended_sum;
        }
    } else {
        long long int boundary_sum = max_prefix_sum + max_suffix_sum;
        if (boundary_sum > result) {
            result = boundary_sum;
        }
    }

    return result;
}

int main() {
    int arr1[] = {1, -2, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 5;
    printf("%lld\n", maxSubArraySum(arr1, n1, k1));

    int arr2[] = {-1, -2, -3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 3;
    printf("%lld\n", maxSubArraySum(arr2, n2, k2));

    int arr3[] = {1, 2, 3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int k3 = 2;
    printf("%lld\n", maxSubArraySum(arr3, n3, k3));

    return 0;
}