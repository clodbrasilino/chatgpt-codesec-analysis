#include <stdbool.h>

bool areArraysEqual(int* arr1, int size1, int* arr2, int size2) {
    if (size1 != size2) {
        return false;
    }
    
    for (int i = 0; i < size1; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    
    return true;
}