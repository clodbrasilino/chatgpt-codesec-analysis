int findOperations(int arr[], int n, int k) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int max_val = arr[0];
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int min_val = arr[0];
    for (int i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
         */
        max_val = max(max_val, arr[i]);
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  implicit declaration of function 'min' [-Wimplicit-function-declaration]
         */
        min_val = min(min_val, arr[i]);
    }
    int operations = 0;
    while (max_val - min_val > 0) {
        max_val -= k;
        min_val += k;
        operations++;
    }
    return operations;
}