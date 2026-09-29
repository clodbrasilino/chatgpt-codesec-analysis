#include <stdbool.h>

bool checkArrPattern(int arr[], int size, int patterns[], int patternSize) {
    int patternIndex = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'patterns[patternIndex]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == patterns[patternIndex]) {
            patternIndex++;
        }
        if (patternIndex == patternSize) {
            return true;
        }
    }
    return false;
}