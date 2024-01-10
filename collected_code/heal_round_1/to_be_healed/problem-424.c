#include <stdio.h>
#include <string.h>

void extractRearIndexElement(char array[][100], int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'array[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        int length = strlen(array[i]);
        if (length > 0) {
            printf("%c\n", array[i][length-1]);
        }
    }
}