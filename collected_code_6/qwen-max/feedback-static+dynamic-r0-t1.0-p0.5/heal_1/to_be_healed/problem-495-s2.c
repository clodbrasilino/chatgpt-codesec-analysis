#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strncat'
  */

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    char result[1024];
    regmatch_t pmatch[1];
    int nmatch = 1;
    int pos = 0;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    while (regexec(&regex, str + pos, nmatch, pmatch, 0) == 0) {
        int match_start = pmatch[0].rm_so + pos;
        int match_end = pmatch[0].rm_eo + pos;
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        int len = match_end - match_start;

        if (pos > 0) {
            /* Possible weaknesses found:
             *  include the header <string.h> or explicitly provide a declaration for 'strncat'
             *  Uninitialized variable: result [legacyUninitvar]
             *  implicit declaration of function 'strncat' [-Wimplicit-function-declaration]
             *  call to undeclared library function 'strncat' with type 'char *(char *, const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            strncat(result, str + pos, match_start - pos);
        }
        pos = match_end;
    }

    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    if (pos < (int)strlen(str)) {
        strncat(result, str + pos, strlen(str) - pos);
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strcpy'
     *  call to undeclared library function 'strcpy' with type 'char *(char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strcpy'
     *  implicit declaration of function 'strcpy' [-Wimplicit-function-declaration]
     */
    strcpy(str, result);
    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt StRiNg";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}