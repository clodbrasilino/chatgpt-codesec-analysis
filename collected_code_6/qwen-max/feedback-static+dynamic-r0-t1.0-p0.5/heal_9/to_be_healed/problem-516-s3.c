#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define RADIX 10

void countingSort(int arr[], int n, int exp) {
    int output[n];
    int count[RADIX] = {0};
    int i;

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % RADIX]++;

    for (i = 1; i < RADIX; i++)
        count[i] += count[i - 1];

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % RADIX] - 1] = arr[i];
        count[(arr[i] / exp) % RADIX]--;
    }

    for (i = 0; i < n; i++)
        /* Possible weaknesses found:
         *  Uninitialized variable: output [uninitvar]
         *  Uninitialized variable: output
         */
        arr[i] = output[i];
}

/* Possible weaknesses found:
 *  conflicting types for 'radixsort'; have 'void(int *, int)'
 *  conflicting types for 'radixsort'
 */
void radixsort(int arr[], int n) {
    int m = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > m)
            m = arr[i];
    }

    for (int exp = 1; m / exp > 0; exp *= RADIX) {
        countingSort(arr, n, exp);
    }
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    /* Possible weaknesses found:
     *  too few arguments to function call, expected 4, have 2
     */
    radixsort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    return 0;
}