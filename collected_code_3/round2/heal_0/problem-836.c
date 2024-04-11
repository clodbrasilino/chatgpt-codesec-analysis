#include <stdio.h>
#include <limits.h>

int maxSubArrayLength(int arr[], int n) {
    int max_so_far = INT_MIN, max_ending_here = 0;
    int start =0, end = 0, s=0;

    for (int i=0; i< n; i++ ) {
        max_ending_here += arr[i];

        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }

        if (max_ending_here < 0) {
            max_ending_here = 0;
            s = i + 1;
        }
    }
    return (end - start + 1);
}

int main() {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr)/sizeof(arr[0]);
    int max_len = maxSubArrayLength(arr, n);
    printf("Length of maximum sum subarray is %d\n", max_len);
    return 0;
}