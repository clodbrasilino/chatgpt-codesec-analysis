int findFirstPosition(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;
    int result = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[mid] == target) {
            result = mid;
            high = mid - 1;
        }
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    
    return result;
}