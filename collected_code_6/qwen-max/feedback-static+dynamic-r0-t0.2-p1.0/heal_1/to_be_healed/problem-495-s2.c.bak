#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *p = str;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    int len, offset = 0;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED | REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        len = match[0].rm_eo - match[0].rm_so;
        /* Possible weaknesses found:
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  include '<string.h>' or provide a declaration of 'strlen'
         */
        memmove(p + match[0].rm_so - offset, p + match[0].rm_eo, strlen(p + match[0].rm_eo) + 1);
        p += match[0].rm_so - offset;
        offset += len;
    }

    regfree(&regex);
}

int main() {
    char str[] = "ThiS iS a TeSt StrinG";
    remove_lowercase_substrings(str);
    printf("%s\n", str);
    return 0;
}