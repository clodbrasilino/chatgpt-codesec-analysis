#include <stdio.h>
#include <regex.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void removeSpecialCharacters(char* str) {
    regex_t regex;
    int ret;

    // Compile the regular expression pattern
    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    // Execute the regular expression
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    ret = regexec(&regex, str, 0, NULL, 0);
    if (!ret) {
        // If a match is found, replace special characters with empty string
        regfree(&regex);
        regex_t regex2;
        ret = regcomp(&regex2, "[^a-zA-Z0-9]", REG_EXTENDED);
        /* Possible weaknesses found:
         *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         *  include '<stdlib.h>' or provide a declaration of 'malloc'
         *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
         */
        char* result = (char*)malloc(sizeof(char) * (strlen(str) + 1));
        regmatch_t pmatch;
        int index = 0;

        while (regexec(&regex2, str + index, 1, &pmatch, 0) == 0) {
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(result + index, str + index + pmatch.rm_so, pmatch.rm_eo - pmatch.rm_so);
            index += pmatch.rm_eo - pmatch.rm_so;
        }
        
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(result + index, str + index + pmatch.rm_so, pmatch.rm_eo - pmatch.rm_so);
        /* Possible weaknesses found:
         *  Cannot determine that 'result[0]' is initialized [premium-bughuntingUninit]
         *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
         */
        strcpy(str, result);
        /* Possible weaknesses found:
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'free'
         */
        free(result);
        regfree(&regex2);
    }
    
    regfree(&regex);
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100] = "Hello! How are you? 123";
    removeSpecialCharacters(str);
    printf("%s\n", str);
    return 0;
}