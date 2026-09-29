#include <stdio.h>
#include <stdlib.h>

long long int maxSubArraySum(int a[], int size) {
    long long int max_so_far = a[0];
    long long int curr_max = a[0];

    for (int i = 1; i < size; i++) {
        long long int val = a[i];
        if (curr_max > 0) {
            curr_max += val;
        } else {
            curr_max = val;
        }
        if (curr_max > max_so_far) {
            max_so_far = curr_max;
        }
    }
    return max_so_far;
}

long long int maxSubArraySumRepeated(int a[], int n, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }

    if (k == 1) {
        return maxSubArraySum(a, n);
    }

    long long int array_sum = 0;
    for (int i = 0; i < n; i++) {
        array_sum += a[i];
    }

    int* temp = (int*)malloc(2 * n * sizeof(int));
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2 * n; i++) {
        temp[i] = a[i % n];
    }

    long long int max_two = maxSubArraySum(temp, 2 * n);
    free(temp);

    if (array_sum > 0) {
        return max_two + (array_sum * (k - 2));
    } else {
        return max_two;
    }
}

int main(void) {
    int arr[] = {1, -2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;

    long long int result = maxSubArraySumRepeated(arr, n, k);
    printf("%lld\n", result);

    int arr2[] = {-1, -2, -3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 5;

    long long int result2 = maxSubArraySumRepeated(arr2, n2, k2);
    printf("%lld\n", result2);

    return 0;
}