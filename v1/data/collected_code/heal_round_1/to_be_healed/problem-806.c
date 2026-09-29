#include <stdio.h>
#include <string.h>

int maxRunOfUppercase(char *str) {
    int currRun = 0;
    int maxRun = 0;
    int i;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (i = 0; i < strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            currRun++;
            if (currRun > maxRun) {
                maxRun = currRun;
            }
        } else {
            currRun = 0;
        }
    }

    return maxRun;
}

int main() {
    char str[] = "HelloWORLD";
    int maxRun = maxRunOfUppercase(str);
    
    printf("Maximum run of uppercase characters: %d\n", maxRun);

    return 0;
}