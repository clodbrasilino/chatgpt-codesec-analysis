#include <stdbool.h>

bool areAllCharactersUnique(char* str) {
    int charCount[256] = {0};

    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (charCount[str[i]] > 0) {
            return false;
        }
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        charCount[str[i]]++;
    }

    return true;
}