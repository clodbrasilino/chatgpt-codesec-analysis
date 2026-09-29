#include <stdio.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strncpy'
  */

void extractValues(char* string) {
    regex_t regex;
    regmatch_t matches[1];
    const char* pattern = "\"([^\"]+)\"";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Could not compile regex pattern\n");
        return;
    }

    /* Possible weaknesses found:
     *  Cannot determine that 'string[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int result = regexec(&regex, string, 1, matches, 0);
    if (result == 0) {
        /* Possible weaknesses found:
         *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
         */
        int start = matches[0].rm_so + 1;
        /* Possible weaknesses found:
         *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
         */
        int end = matches[0].rm_eo - 1;
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char extractedValue[end - start + 1];
        /* Possible weaknesses found:
         *  implicit declaration of function 'strncpy' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'strncpy' [-Wbuiltin-declaration-mismatch]
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         *  include '<string.h>' or provide a declaration of 'strncpy'
         *  Cannot determine that 'extractedValue[0]' is initialized [premium-bughuntingUninit]
         */
        strncpy(extractedValue, string + start, end - start);
        extractedValue[end - start] = '\0';
        printf("%s\n", extractedValue);
    } else if (result == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        printf("Error executing regex\n");
    }

    regfree(&regex);
}

int main() {
    char string[] = "The value is \"example\".";
    extractValues(string);
    return 0;
}