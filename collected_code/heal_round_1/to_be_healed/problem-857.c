#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printString(char* str) {
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    printf("%s\n", str);
}

void listStrings(char** strings, int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'strings[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printString(strings[i]);
    }
}

int main() {
    char* strings[] = {"Hello", "World", "C", "Programming"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);
    
    listStrings(strings, numStrings);
    
    return 0;
}
