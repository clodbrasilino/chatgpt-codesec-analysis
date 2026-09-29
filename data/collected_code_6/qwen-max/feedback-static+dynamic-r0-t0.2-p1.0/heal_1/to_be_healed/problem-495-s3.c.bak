#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "[a-z]+";
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    while ((reti = regexec(&regex, str, 1, match, 0)) == 0) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  include '<string.h>' or provide a declaration of 'strlen'
         */
        memmove(str + match[0].rm_so, str + match[0].rm_eo, strlen(str + match[0].rm_eo) + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "TesT123abc456DEF789";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}