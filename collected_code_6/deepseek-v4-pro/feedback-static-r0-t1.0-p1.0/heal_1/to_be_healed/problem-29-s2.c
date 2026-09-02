#include <stdio.h>
#include <stdlib.h>

int findOddOccurrence(const int *arr, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= arr[i];
    }
    return result;
}

int main(void) {
    int arr[] = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr)/sizeof(arr[0])', assigned value is 13
     */
    int n = sizeof(arr) / sizeof(arr[0]);
    
    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     *  Condition 'n<=0' is always false
     */
    if (n <= 0) {
        fprintf(stderr, "Error: Empty array\n");
        return EXIT_FAILURE;
    }
    
    int odd = findOddOccurrence(arr, n);
    printf("Element occurring odd number of times: %d\n", odd);
    
    return EXIT_SUCCESS;
}