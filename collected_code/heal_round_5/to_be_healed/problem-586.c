#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void splitAndAdd(int arr[], int n, int k) {
    if (k > n) {
        return;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    int *temp = (int *)malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'temp' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        temp[i] = arr[i];
    }

    for (int i = 0; i < n - k; i++) {
        arr[i] = arr[i + k];
    }

    for (int i = n - k, j = 0; i < n; i++, j++) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*temp_38 + _20' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of possibly-NULL 'temp' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        arr[i] = temp[j];
    }

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(temp);
}


int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    
    if (k > 0 && k <= n) {
        splitAndAdd(arr, n, k);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}