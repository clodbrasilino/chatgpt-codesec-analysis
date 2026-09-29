#include <string.h>

void concatenateStrings(char str1[], char str2[], char result[]){
    /* Possible weaknesses found:
     *  Cannot determine that 'result[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'str1[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(result, str1);
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when concatenating to destination  [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or  snprintf (warning: strncat is easily misused).
     *  Cannot determine that 'str2[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    strcat(result, str2);
}