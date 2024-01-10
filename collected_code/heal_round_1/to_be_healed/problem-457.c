#include <stdio.h>
#include <limits.h>

// Function to find sublist with minimum length
void findMinLength(int arr[], int n) {
    int minLen = INT_MAX;   // Initialize minimum length as maximum integer value
    int startPos = -1;      // Initialize starting position of sublist
    
    // Traverse through array to find sublist with minimum length
    for(int i = 0; i < n; i++) {
        int len = 0;   // Initialize length of current sublist
        
        // Check all sublists starting from index i
        for(int j = i; j < n; j++) {
            len++;   // Increase length of sublist
            
            // If sublist length is smaller than current minimum length, update the minimum length and starting position
            if(len < minLen) {
                minLen = len;
                startPos = i;
            }
        }
    }
    
    // Print the sublist with minimum length
    printf("Sublist with minimum length: ");
    for(int i = startPos; i < startPos + minLen; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%d ", arr[i]);
    }
}

int main() {
    int arr[] = {3, 2, 7, 1, 5, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    findMinLength(arr, n);
    
    return 0;
}