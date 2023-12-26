#include <stdbool.h>

bool isValidParentheses(char* s) {
    int count = 0;
    
    /* Possible weaknesses found:
     *  Cannot determine that 's[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; s[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 's[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (s[i] == '(')
            count++;
        /* Possible weaknesses found:
         *  Cannot determine that 's[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        else if (s[i] == ')') {
            if (count == 0)
                return false;
            count--;
        }
    }
    
    return count == 0;
}