#include <stdio.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

void removeMultipleSpaces(char* str) {
    regex_t regex;
    regcomp(&regex, "  +", REG_EXTENDED);

    regmatch_t match;
    int offset = 0;
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     */
    int len = strlen(str);
    while (offset < len && regexec(&regex, str + offset, 1, &match, 0) == 0) {
        int start = match.rm_so + offset;
        int end = match.rm_eo + offset;

        int numSpaces = end - start;
        int numCharsAfterSpaces = len - end;
        /* Possible weaknesses found:
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  include '<string.h>' or provide a declaration of 'memmove'
         *  incompatible implicit declaration of built-in function 'memmove' [-Wbuiltin-declaration-mismatch]
         */
        memmove(str + start, str + end, numCharsAfterSpaces);
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'memset' [-Wbuiltin-declaration-mismatch]
         *  include '<string.h>' or provide a declaration of 'memset'
         *  implicit declaration of function 'memset' [-Wimplicit-function-declaration]
         */
        memset(str + len - numSpaces, ' ', numSpaces);

        len -= numSpaces;
        offset = start + 1;
    }

    regfree(&regex);
}

int main() {
    char str[] = "This   is  a    string   with    multiple   spaces.";
    printf("Before removing multiple spaces: %s\n", str);

    removeMultipleSpaces(str);
    printf("After removing multiple spaces: %s\n", str);

    return 0;
}