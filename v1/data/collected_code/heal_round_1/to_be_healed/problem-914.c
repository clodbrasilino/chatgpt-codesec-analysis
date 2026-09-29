#include <stdbool.h>

bool isMadeOfAlternatingCharacters(char *str) {
    int i = 0;
    int length = 0;
    
    //get the length of the string
    /* Possible weaknesses found:
     *  Cannot determine that 'str[length]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (str[length] != '\0') {
        length++;
    }
    
    //check if the string has only two characters
    if (length != 2) {
        return false;
    }
    
    //check if the characters alternate
    while (i < length - 1) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (str[i] == str[i + 1]) {
            return false;
        }
        i++;
    }
    
    return true;
}