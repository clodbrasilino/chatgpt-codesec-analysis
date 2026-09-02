#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    /* Possible weaknesses found:
     *  The scope of the variable 'reti' can be reduced. [variableScope]
     */
    int reti;
    char *ptr = str;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (1) {
        reti = regexec(&regex, ptr, 1, pmatch, 0);
        if (reti == REG_NOMATCH) {
            break;
        } else if (reti != 0) {
            regfree(&regex);
            return;
        }

        /* Possible weaknesses found:
         *  include '<string.h>' or provide a declaration of 'strlen'
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         */
        memmove(ptr + pmatch[0].rm_so, ptr + pmatch[0].rm_eo, strlen(ptr + pmatch[0].rm_eo) + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt sTrInG wItH lOwErCaSe ChArAcTeRs";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}