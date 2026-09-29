#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void clean_string(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *p = str;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        int len = match[0].rm_eo - match[0].rm_so;
        /* Possible weaknesses found:
         *  include '<string.h>' or provide a declaration of 'strlen'
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         */
        memmove(p + match[0].rm_so, p + match[0].rm_eo, strlen(p + match[0].rm_eo) + 1);
        p += len;
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello! This is a test. 12345";
    clean_string(input);
    printf("%s\n", input);
    return 0;
}