#include <stdio.h>

char findFirstRepeatedChar(char *string) {
    int count[256] = {0}; // assuming ASCII character set

    /* Possible weaknesses found:
     *  Cannot determine that 'string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; string[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (count[string[i]] == 1)
            /* Possible weaknesses found:
             *  Cannot determine that 'string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            return string[i];
        
        /* Possible weaknesses found:
         *  Cannot determine that 'string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        count[string[i]]++;
    }

    return '\0'; // no repeated characters found 
}

int main() {
    char string[] = "example";
    char result = findFirstRepeatedChar(string);

    printf("The first repeated character is: %c\n", result);

    return 0;
}