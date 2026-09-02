#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char pattern[] = "[a-z]+";
    int rc;

    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while ((rc = regexec(&regex, str, 1, pmatch, 0)) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        /* Possible weaknesses found:
         *  include '<string.h>' or provide a declaration of 'strlen'
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         */
        memmove(str + start, str + end, strlen(str + end) + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt sTrInG wItH lOwErCaSe ChArAcTeRs.";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}