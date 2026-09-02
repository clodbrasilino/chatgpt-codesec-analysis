#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int maxProductSubsequence(int arr[], int n) {
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    int *max_end = (int *)malloc(n * sizeof(int));
    if (max_end == NULL) return 0;
    
    for (int i = 0; i < n; ++i) {
        max_end[i] = arr[i];
    }
    
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j] && max_end[i] < max_end[j] * arr[i]) {
                max_end[i] = max_end[j] * arr[i];
            }
        }
    }
    
    int max_product = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (max_product < max_end[i]) {
            max_product = max_end[i];
        }
    }
    
    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(max_end);
    return max_product;
}

int main() {
    int arr[] = {3, 100, 4, 5, 150, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = maxProductSubsequence(arr, n);
    printf("Maximum product of an increasing subsequence is %d\n", result);
    return 0;
}