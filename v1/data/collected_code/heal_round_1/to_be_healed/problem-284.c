#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool checkEquality(char *list[], int size, char *str) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (strcmp(list[i], str) != 0) {
            return false;
        }
    }
    return true;
}