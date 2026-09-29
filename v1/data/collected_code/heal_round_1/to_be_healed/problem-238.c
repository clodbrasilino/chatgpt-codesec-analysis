#include <stdio.h>
#include <string.h>

int countSubstrings(char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int length = strlen(str);
    int count = 0;
    
    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            count++;
        }
    }
    
    return count;
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
    scanf("%[^\n]", str);
    
    int result = countSubstrings(str);
    printf("Number of non-empty substrings: %d\n", result);
    
    return 0;
}