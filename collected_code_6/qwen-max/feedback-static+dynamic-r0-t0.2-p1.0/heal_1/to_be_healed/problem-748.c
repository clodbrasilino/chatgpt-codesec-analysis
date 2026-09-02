#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void insert_spaces(char *str) {
    regex_t reg;
    regmatch_t match[1];
    char pattern[] = "([A-Z][^A-Z]*)";
    /* Possible weaknesses found:
     *  Unused variable: reti [unusedVariable]
     */
    int reti;

    if (regcomp(&reg, pattern, REG_EXTENDED|REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    while (regexec(&reg, str, 1, match, 0) == 0) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  include '<string.h>' or provide a declaration of 'strlen'
         */
        memmove(str + match[0].rm_eo + 1, str + match[0].rm_eo, strlen(str + match[0].rm_eo) + 1);
        str[match[0].rm_eo] = ' ';
        str += match[0].rm_eo + 1;
    }

    regfree(&reg);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    insert_spaces(str);
    printf("%s\n", str);
    return 0;
}