#include <stdio.h>
#include <string.h>

void abbreviateRoad(char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int len = strlen(str);
    for (int i = 0; i < len - 3; i++) {
        if (str[i] == 'r' && str[i+1] == 'o' && str[i+2] == 'a' && str[i+3] == 'd') {
            str[i+2] = 'd';
            str[i+3] = '.';
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100];
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
     */
    scanf("%[^\n]s", str);
    abbreviateRoad(str);
    printf("Abbreviated string: %s\n", str);
    
    return 0;
}
