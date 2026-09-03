#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

void sanitize_string(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *p = str;
    /* Possible weaknesses found:
     *  Unused variable: i [unusedVariable]
     */
    int len, i;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (*p) {
        if (regexec(&regex, p, 1, match, 0) == 0) {
            /* Possible weaknesses found:
             *  include the header <string.h> or explicitly provide a declaration for 'strlen'
             *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
             */
            len = strlen(p + match[0].rm_eo);
            /* Possible weaknesses found:
             *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
             *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'memmove'
             *  include '<string.h>' or provide a declaration of 'memmove'
             */
            memmove(p + match[0].rm_so, p + match[0].rm_eo, len + 1);
        } else {
            p++;
        }
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    sanitize_string(input);
    printf("%s\n", input);
    return 0;
}