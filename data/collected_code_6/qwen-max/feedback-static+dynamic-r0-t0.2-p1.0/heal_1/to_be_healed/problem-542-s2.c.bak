#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *ptr = str;
    int reti;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        return;
    }

    while ((reti = regexec(&regex, ptr, 1, match, 0)) == 0) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  include '<string.h>' or provide a declaration of 'strlen'
         */
        memmove(ptr + 1, ptr + match[0].rm_eo, strlen(ptr + match[0].rm_eo) + 1);
        *ptr = ':';
        ptr += 2;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}