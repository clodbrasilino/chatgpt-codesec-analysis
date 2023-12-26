int findSmallestMissingElement(int arr[], int size) {
    int low = 0;
    int high = size - 1;
  
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[low]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (arr[low] != 0) {
        return 0;
    }
  
    while (low <= high) {
        int mid = low + (high - low) / 2;
      
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[low]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[mid] - arr[low] > 1) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
  
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[low]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    return arr[low] - 1;
}