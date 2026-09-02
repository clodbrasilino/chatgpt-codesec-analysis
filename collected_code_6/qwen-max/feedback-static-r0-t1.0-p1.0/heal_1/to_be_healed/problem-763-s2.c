#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findMinDifference(int arr[], int n) {
    int min_diff = INT_MAX;
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
             *  include the header <stdlib.h> or explicitly provide a declaration for 'abs'
             *  call to undeclared library function 'abs' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            int diff = abs(arr[i] - arr[j]);
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
    }
    return min_diff;
}

int main() {
    int arr[] = {5, 3, 8, 2, 9};
    int n = sizeof(arr)/sizeof(arr[0]);
    int result = findMinDifference(arr, n);
    printf("Minimum difference: %d\n", result);
    return 0;
}