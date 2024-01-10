#include <stdio.h>

int matchString(char *string) {
    int i = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (string[i] != '\0') {
        /* Possible weaknesses found:
         *  Cannot determine that 'string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (string[i] == 'a') {
            /* Possible weaknesses found:
             *  Cannot determine that 'string[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (string[i + 1] == 'b' || string[i + 1] == '\0') {
                return 1;
            }
        }
        i++;
    }
    return 0;
}

int main() {
    char *input = "abc";
    int result = matchString(input);
    
    if (result) {
        printf("Match found");
    } else {
        printf("Match not found");
    }
    
    return 0;
}