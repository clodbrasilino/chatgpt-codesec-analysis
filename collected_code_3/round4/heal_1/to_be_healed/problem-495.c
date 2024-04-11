#include <stdio.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void removeLowercaseSubstrings(char *str) {
    regex_t regex;
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    char *newStr = (char *)malloc(strlen(str) + 1);
    int index = 0;

    regcomp(&regex, "[a-z]+", REG_EXTENDED);

    char *p = str;
    regmatch_t match;

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        int len = match.rm_so;
        strncpy(newStr + index, p, len);
        index += len;
        p += match.rm_eo;
    }

    strcpy(newStr + index, p);
    strcpy(str, newStr);

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(newStr);
    regfree(&regex);
}

int main() {
    char str[] = "HelloWorld";
    removeLowercaseSubstrings(str);
    printf("%s\n", str);
    return 0;
}