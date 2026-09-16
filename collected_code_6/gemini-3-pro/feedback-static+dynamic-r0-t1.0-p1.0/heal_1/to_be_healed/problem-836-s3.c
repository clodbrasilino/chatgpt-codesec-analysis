#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int maxSubArrayLength(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int maxSum = arr[0];
    int currentSum = arr[0];
    int maxLength = 1;
    int currentLength = 1;
    /* Possible weaknesses found:
     *  Variable 'maxStart' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'maxStart' can be reduced. [variableScope]
     */
    int maxStart = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'maxEnd' can be reduced. [variableScope]
     *  Variable 'maxEnd' is assigned a value that is never used. [unreadVariable]
     */
    int maxEnd = 0;
    int currentStart = 0;

    for (int i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Invalid test for overflow 'arr[i]>currentSum+arr[i]'; signed integer overflow is undefined behavior. Some mainstream compilers removes handling of overflows when optimising the code and change the code to 'currentSum<0'. [invalidTestForOverflow]
         */
        if (arr[i] > currentSum + arr[i]) {
            currentSum = arr[i];
            currentStart = i;
            currentLength = 1;
        } else {
            currentSum = currentSum + arr[i];
            currentLength++;
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            /* Possible weaknesses found:
             *  Variable 'maxStart' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'maxStart' is never read [deadcode.DeadStores]
             */
            maxStart = currentStart;
            /* Possible weaknesses found:
             *  Variable 'maxEnd' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'maxEnd' is never read [deadcode.DeadStores]
             */
            maxEnd = i;
            maxLength = currentLength;
        } else if (currentSum == maxSum) {
            if (currentLength > maxLength) {
                maxLength = currentLength;
                /* Possible weaknesses found:
                 *  Variable 'maxStart' is assigned a value that is never used. [unreadVariable]
                 *  Value stored to 'maxStart' is never read [deadcode.DeadStores]
                 */
                maxStart = currentStart;
                /* Possible weaknesses found:
                 *  Variable 'maxEnd' is assigned a value that is never used. [unreadVariable]
                 *  Value stored to 'maxEnd' is never read [deadcode.DeadStores]
                 */
                maxEnd = i;
            }
        }
    }

    return maxLength;
}

int main(void) {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int length = maxSubArrayLength(arr, n);

    printf("Length of the subarray with maximum sum: %d\n", length);

    return 0;
}