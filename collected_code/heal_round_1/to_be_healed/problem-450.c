#include <stdio.h>

void extractStrings(char **list, int size, char** output) {
    for(int i=0; i<size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        output[i] = list[i];
    }
}

int main() {
    char *stringList[] = {"Hello", "World", "How", "Are", "You"};
    int stringsToExtract = 3;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     *  Cannot determine that 'extractedStrings[stringsToExtract]' is initialized [premium-bughuntingUninit]
     */
    char *extractedStrings[stringsToExtract];

    extractStrings(stringList, stringsToExtract, extractedStrings);

    for(int i=0; i<stringsToExtract; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'extractedStrings[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%s\n", extractedStrings[i]);
    }

    return 0;
}