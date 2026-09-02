#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int maxSubArraySum(int *arr, int n) {
    int max_so_far = INT_MIN, max_ending_here = 0;
  
    for (int i = 0; i < n; i++) {
        max_ending_here = max_ending_here + arr[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;
        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}

int arrayRepeatKTimesMaxSum(int *arr, int n, int k) {
    int sum = 0;
    int max_kadane = maxSubArraySum(arr, n);
    int max_prefix_sum = 0, max_suffix_sum = 0, temp = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];
        temp += arr[i];
        max_prefix_sum = (temp > max_prefix_sum) ? temp : max_prefix_sum;
    }

    temp = 0;
    for (int i = n - 1; i >= 0; i--) {
        temp += arr[i];
        max_suffix_sum = (temp > max_suffix_sum) ? temp : max_suffix_sum;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'max'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
     */
    int maxSum = (k == 1) ? max_kadane : max(max_kadane, max_prefix_sum + max_suffix_sum + (k-2) * ((sum > 0) ? sum : 0));
    return maxSum;
}

int main() {
    int arr[] = {1, -2, 1, 2, -1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;
    printf("%d\n", arrayRepeatKTimesMaxSum(arr, n, k));
    return 0;
}