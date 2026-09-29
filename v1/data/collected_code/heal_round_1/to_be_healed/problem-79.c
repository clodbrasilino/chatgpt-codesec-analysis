#include <stdbool.h>

bool isLengthOdd(char* word) {
    int length = 0;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'word[length]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (word[length] != '\0') {
        length++;
    }
    
    return length % 2 != 0;
}