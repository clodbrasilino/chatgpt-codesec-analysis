#include <stdbool.h>

bool checkValue(int value, int sequence[], int length) {
    for (int i = 0; i < length; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'sequence[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (sequence[i] == value) {
            return true;
        }
    }
    return false;
}