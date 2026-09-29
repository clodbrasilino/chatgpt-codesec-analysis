#include <stdbool.h>

int sumNonRepeatedElements(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        bool repeated = false;
        for (int j = 0; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (i != j && arr[i] == arr[j]) {
                repeated = true;
                break;
            }
        }
        if (!repeated) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            sum += arr[i];
        }
    }
    return sum;
}