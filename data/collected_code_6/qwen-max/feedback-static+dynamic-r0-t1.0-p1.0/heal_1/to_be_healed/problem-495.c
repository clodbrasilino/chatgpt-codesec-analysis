#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    char *pattern = "[a-z]+";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    regmatch_t matches[1];
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        int match_start = matches[0].rm_so;
        int match_end = matches[0].rm_eo;
        /* Possible weaknesses found:
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  include '<string.h>' or provide a declaration of 'strlen'
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         */
        memmove(str + match_start, str + match_end, strlen(str + match_end) + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "HeLlO WoRlD";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}