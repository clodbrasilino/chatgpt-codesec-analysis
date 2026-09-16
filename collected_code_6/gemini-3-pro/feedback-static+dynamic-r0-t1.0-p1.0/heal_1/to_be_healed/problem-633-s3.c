#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
long long sumXOR(int arr[], int n) {
    long long sum = 0;
    for (int i = 0; i < 32; i++) {
        int zero_count = 0;
        int one_count = 0;
        for (int j = 0; j < n; j++) {
            /* Possible weaknesses found:
             * UBSan: left shift of 1 by 31 places cannot be represented in type 'int'
             */
            if (arr[j] & (1 << i)) {
                one_count++;
            } else {
                zero_count++;
            }
        }
        sum += (long long)zero_count * one_count * (1LL << i);
    }
    return sum;
}

int main(void) {
    int arr[] = {7, 3, 5};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr)/sizeof(arr[0])', assigned value is 3
     */
    int n = sizeof(arr) / sizeof(arr[0]);
    
    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     */
    if (n <= 0) {
        return 1;
    }

    long long result = sumXOR(arr, n);
    printf("%lld\n", result);
    
    return 0;
}