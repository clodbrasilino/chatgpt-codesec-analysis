#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void replace_chars(char *str, size_t len) {
    regex_t regex;
    regmatch_t match[1];
    char *ptr = str;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, ptr, 1, match, 0) == 0) {
        size_t match_len = match[0].rm_eo - match[0].rm_so;
        size_t remaining_len = len - (ptr - str);
        /* Possible weaknesses found:
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         */
        memmove(ptr + 1, ptr + match_len, remaining_len - match_len + 1);
        *ptr = ':';
        ptr += 2;
        len -= match_len - 1;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}