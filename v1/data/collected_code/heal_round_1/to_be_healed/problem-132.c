#include <stdio.h>
#include <string.h>

void tupleToString(char *str, int tuple) {
    /* Possible weaknesses found:
     *   Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or  vsnprintf. Risk is low because the source has a constant maximum length.
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    sprintf(str, "(%d, %d, %d)", tuple >> 16, (tuple >> 8) & 0xFF, tuple & 0xFF);
}

int main() {
    int tuple = 0x123456;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[32];
    
    tupleToString(str, tuple);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
     */
    printf("%s\n", str);
    
    return 0;
}