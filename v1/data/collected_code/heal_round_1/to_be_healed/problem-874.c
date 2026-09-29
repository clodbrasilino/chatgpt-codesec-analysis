#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkConcatenation(char *str1, char *str2) {
    /* Possible weaknesses found:
     *  Cannot determine that 'str1[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len1 = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str2[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int len2 = strlen(str2);
    
    if (len1 % len2 != 0) {
        return false;
    }
    
    for (int i = 0; i < len1; i += len2) {
        if (strncmp(str1 + i, str2, len2) != 0) {
            return false;
        }
    }
    
    return true;
}

int main() {
    char str1[] = "abcabcabc";
    char str2[] = "abc";
    
    if (checkConcatenation(str1, str2)) {
        printf("String is a concatenation of another string\n");
    } else {
        printf("String is not a concatenation of another string\n");
    }
    
    return 0;
}