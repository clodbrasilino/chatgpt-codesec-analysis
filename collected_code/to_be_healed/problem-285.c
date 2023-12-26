#include <stdio.h>

int matchString(char* str) {
    int i = 0;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while(str[i] != '\0') {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if(str[i] == 'a') {
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'str[i+2]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if(str[i + 1] == 'b' && (str[i + 2] == 'b' || str[i + 2] == '\0')) {
                return 1;
            }
        }
        i++;
    }
    
    return 0;
}

int main() {
    char str[] = "abb";
    
    if(matchString(str)) {
        printf("Match found\n");
    } else {
        printf("No match found\n");
    }
    
    return 0;
}