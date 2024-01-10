void assignPairs(int arr[], int n) {
    for (int i = 0; i < n; i += 2) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        arr[i + 1] = arr[i];
    }
}