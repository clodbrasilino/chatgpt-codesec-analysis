#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

void add_spaces(char *str) {
    regex_t regex;
    regcomp(&regex, "[A-Z]", REG_EXTENDED);
    
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     */
    char *result = (char *) malloc(2 * strlen(str) * sizeof(char));
    size_t i = 0;
    
    while (*str != '\0') {
        if (regexec(&regex, str, 0, NULL, 0) == REG_NOMATCH) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[i++] = *str++;
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[i++] = ' ';
            result[i++] = *str++;
        }
    }
    
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    result[i] = '\0';
    
    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strcpy'
     *  incompatible implicit declaration of built-in function 'strcpy' [-Wbuiltin-declaration-mismatch]
     *  Cannot determine that 'result[0]' is initialized [premium-bughuntingUninit]
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     *  implicit declaration of function 'strcpy' [-Wimplicit-function-declaration]
     */
    strcpy(str, result);
    free(result);
}

int main() {
    char str[] = "WriteACFunctionToPutSpacesBetweenWordsStartingWithCapitalLetters";
    add_spaces(str);
    printf("%s\n", str);
    return 0;
}