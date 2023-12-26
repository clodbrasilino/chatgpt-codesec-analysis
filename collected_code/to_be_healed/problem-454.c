#include <stdio.h>
#include <stdbool.h>

bool containsZ(char *word) {
    int i = 0;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'word[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (word[i] != '\0') {
        /* Possible weaknesses found:
         *  Cannot determine that 'word[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
        i++;
    }
    
    return false;
}