#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  expected 'float *' but argument is of type 'int *'
 */
void convertToFloat(float* arr, int len) {
    for (int i = 0; i < len; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        arr[i] = (float) arr[i];
    }
}

int main() {
    // Example usage
    int len = 5;
    int arr[] = {1, 2, 3, 4, 5};

    /* Possible weaknesses found:
     *  passing argument 1 of 'convertToFloat' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    convertToFloat(arr, len);

    for (int i = 0; i < len; i++) {
        printf("%.2f ", arr[i]);
    }

    return 0;
}