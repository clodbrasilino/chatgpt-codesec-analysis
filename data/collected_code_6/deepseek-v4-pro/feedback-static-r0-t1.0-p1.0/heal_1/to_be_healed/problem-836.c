#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int max_subarray_length(int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int max_sum = arr[0];
    int current_sum = arr[0];
    int max_length = 1;
    int current_length = 1;
    int start = 0;
    /* Possible weaknesses found:
     *  Variable 'max_start' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'max_start' can be reduced. [variableScope]
     */
    int max_start = 0;
    /* Possible weaknesses found:
     *  Variable 'max_end' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'max_end' can be reduced. [variableScope]
     */
    int max_end = 0;

    for (int i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Invalid test for overflow 'arr[i]>current_sum+arr[i]'; signed integer overflow is undefined behavior. Some mainstream compilers removes handling of overflows when optimising the code and change the code to 'current_sum<0'. [invalidTestForOverflow]
         */
        if (arr[i] > current_sum + arr[i]) {
            current_sum = arr[i];
            current_length = 1;
            start = i;
        } else {
            current_sum = current_sum + arr[i];
            current_length++;
        }

        if (current_sum > max_sum ||
            (current_sum == max_sum && current_length > max_length)) {
            max_sum = current_sum;
            max_length = current_length;
            /* Possible weaknesses found:
             *  Value stored to 'max_start' is never read [deadcode.DeadStores]
             *  Variable 'max_start' is assigned a value that is never used. [unreadVariable]
             */
            max_start = start;
            /* Possible weaknesses found:
             *  Value stored to 'max_end' is never read [deadcode.DeadStores]
             *  Variable 'max_end' is assigned a value that is never used. [unreadVariable]
             */
            max_end = i;
        }
    }

    return max_length;
}

int main(void) {
    int arr1[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", max_subarray_length(arr1, n1));

    int arr2[] = {1, -2, 3, -1, 2, 1, -5, 4};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", max_subarray_length(arr2, n2));

    int arr3[] = {-1, -2, -3, -4, -5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", max_subarray_length(arr3, n3));

    int arr4[] = {5, 4, -1, 7, 8};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", max_subarray_length(arr4, n4));

    int arr5[] = {1};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%d\n", max_subarray_length(arr5, n5));

    int arr6[] = {};
    int n6 = sizeof(arr6) / sizeof(arr6[0]);
    printf("%d\n", max_subarray_length(arr6, n6));

    return 0;
}