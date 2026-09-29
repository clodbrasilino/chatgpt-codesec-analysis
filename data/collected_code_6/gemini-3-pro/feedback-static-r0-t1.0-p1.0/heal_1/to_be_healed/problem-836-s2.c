#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findMaxSumSubarrayLength(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    long long max_sum = INT_MIN;
    long long current_sum = 0;
    int max_len = 0;
    int current_len = 0;
    int start = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'max_start' can be reduced. [variableScope]
     *  Variable 'max_start' is assigned a value that is never used. [unreadVariable]
     */
    int max_start = 0;

    for (int i = 0; i < n; i++) {
        current_sum += arr[i];
        current_len++;

        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_len = current_len;
            /* Possible weaknesses found:
             *  Value stored to 'max_start' is never read [deadcode.DeadStores]
             *  Variable 'max_start' is assigned a value that is never used. [unreadVariable]
             */
            max_start = start;
        } else if (current_sum == max_sum) {
            if (current_len > max_len) {
                max_len = current_len;
                /* Possible weaknesses found:
                 *  Value stored to 'max_start' is never read [deadcode.DeadStores]
                 *  Variable 'max_start' is assigned a value that is never used. [unreadVariable]
                 */
                max_start = start;
            }
        }

        if (current_sum < 0) {
            current_sum = 0;
            current_len = 0;
            start = i + 1;
        }
    }

    return max_len;
}

int main() {
    int arr[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr)/sizeof(arr[0])', assigned value is 9
     */
    int n = sizeof(arr) / sizeof(arr[0]);

    /* Possible weaknesses found:
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     */
    if (n > 0) {
        int length = findMaxSumSubarrayLength(arr, n);
        printf("Length of subarray with maximum sum is: %d\n", length);
    }

    return 0;
}