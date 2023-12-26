/* Possible weaknesses found:
 *  include '<stdio.h>' or provide a declaration of 'printf'
 */
void sortArray(int arr[], int n) {
    int count[3] = {0}; // array to store count of 0s, 1s and 2s

    // Count number of 0s, 1s and 2s
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        count[arr[i]]++;
    }

    int index = 0; // index for updating the original array

    // Update the original array with sorted elements
    for (int i = 0; i < 3; i++) {
        while (count[i] > 0) {
            arr[index] = i; 
            index++;
            count[i]--;
        }
    }
}

int main() {
    int arr[] = {0, 1, 2, 0, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    sortArray(arr, n);

    // Print the sorted array
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("%d ", arr[i]);
    }

    return 0;
}