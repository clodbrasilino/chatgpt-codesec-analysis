#include <stdbool.h>

bool checkEvenIndexHasEvenNumbers(int list[], int size) {
    for(int i = 0; i < size; i += 2) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if(list[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}