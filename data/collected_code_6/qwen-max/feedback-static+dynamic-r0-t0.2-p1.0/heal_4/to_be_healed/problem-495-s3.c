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

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    int offset = 0;

    while (regexec(&regex, str + offset, 1, match, 0) == 0) {
        /* Possible weaknesses found:
         *  Variable 'len_after' is assigned a value that is never used. [unreadVariable]
         */
        size_t len_after = match[0].rm_eo - match[0].rm_so + offset;
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
        memmove(str + offset + match[0].rm_so, str + offset + match[0].rm_eo, strlen(str + offset + match[0].rm_eo) + 1);
        offset += match[0].rm_so;
    }

    regfree(&regex);
}

int main() {
    char input[] = "TesT123abc456DEF789";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}