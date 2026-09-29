#include <stdio.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void camelToSnake(char *str) {
    char pattern[] = "([A-Z])";
    char replacement[] = "_\\1";
    regex_t regex;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation failed");
        return;
    }
    
    char *result = NULL;
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'REG_EBUF' undeclared (first use in this function); did you mean 'REG_EBRACE'?
     */
    int length = regerror(REG_EBUF, &regex, NULL, 0);
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     */
    length += strlen(str) + 1;
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    result = malloc(length);
    
    regmatch_t match;
    int offset = 0;
    int status = 0;
    int i = 0;
    
    while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        int start = match.rm_so;
        int end = match.rm_eo;
        int matchedLength = end - start;
        
        /* Possible weaknesses found:
         *  include '<string.h>' or provide a declaration of 'strncpy'
         *  implicit declaration of function 'strncpy' [-Wimplicit-function-declaration]
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         *  incompatible implicit declaration of built-in function 'strncpy' [-Wbuiltin-declaration-mismatch]
         */
        strncpy(result + i, str + offset, start);
        i += start;
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        strncpy(result + i, replacement, strlen(replacement));
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        i += strlen(replacement);
        
        offset += end;
    }
    
    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strcpy'
     *  incompatible implicit declaration of built-in function 'strcpy' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'strcpy' [-Wimplicit-function-declaration]
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(result + i, str + offset);
    printf("%s\n", result);
    
    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(result);
    regfree(&regex);
}

int main() {
    char input[] = "camelCaseString";
    camelToSnake(input);
    
    return 0;
}