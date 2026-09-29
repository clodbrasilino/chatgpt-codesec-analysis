#include <string.h>
#include <regex.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char *removeLowercase(char *str)  {
    regex_t regex;
    regmatch_t matches[2];
    char *newStr = NULL;
    char *pattern = "[a-z]+";

    if (regcomp(&regex, pattern, REG_EXTENDED))  {
        return NULL;
    }
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    newStr = (char*) malloc(strlen(str)+1);
    if (!newStr) {
        regfree(&regex);
        return NULL;
    }
    strcpy(newStr, str);

    while(!regexec(&regex, newStr, 2, matches, 0)) {
        memcpy(newStr+matches[0].rm_so,
               newStr+matches[0].rm_eo,
               strlen(newStr) - matches[0].rm_eo + 1);
    }

    regfree(&regex);
    return newStr;
}

int main()  {
    char input[] = "HeLlO WoRlD!";
    char *output = removeLowercase(input);
    /* Possible weaknesses found:
     *  use of NULL 'output' where non-null expected [CWE-476] [-Wanalyzer-null-argument]
     */
    printf("%s\n", output);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     */
    free(output);
    return 0;
}