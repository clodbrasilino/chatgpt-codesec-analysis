#include <stdio.h>

// Function to get the maximum value in the array
int getMax(int arr[], int n) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] > max) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            max = arr[i];
        }
    }
    return max;
}

// Function to perform counting sort according to the digit represented by exp
void countSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};
    
    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        count[(arr[i] / exp) % 10]++;
    }
    
    // Change count[i] so that count[i] contains actual
    // position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Build the output array
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = n - 1; i >= 0; i--) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        count[(arr[i] / exp) % 10]--;
    }
    
    // Copy the output array to arr[] so that arr[] contains
    // sorted numbers according to current digit
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Radix sort function
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    
    // Perform counting sort for every digit
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    radixSort(arr, n);
    
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}