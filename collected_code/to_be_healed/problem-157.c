#include <stdio.h>

// Function to reflect the run-length encoding from a list
void runLengthEncoding(int arr[], int n) {
    int i, j, count;
    for (i = 0; i < n; i++) {
        // Count occurrences of current element
        count = 1;
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        while (i < n - 1 && arr[i] == arr[i + 1]) {
            count++;
            i++;
        }
        
        // Print the current element and its run-length
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%d%d", arr[i], count);
    }
}

int main() {
    int arr[] = {1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    runLengthEncoding(arr, n);
    return 0;
}