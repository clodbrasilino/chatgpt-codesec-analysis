#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void add_spaces_between_capital_letters(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "([a-z])([A-Z])";
    /* Possible weaknesses found:
     *  Variable 'replacement' is assigned a value that is never used. [unreadVariable]
     */
    char replacement[] = "\\1 \\2";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    int pos = 0;
    while (regexec(&regex, str + pos, 1, match, 0) == 0) {
        int start = pos + match[0].rm_so;
        int end = pos + match[0].rm_eo;

        /* Possible weaknesses found:
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         */
        memmove(str + start + 1, str + start, end - start + 1);
        str[start] = ' ';
        pos = start + 1;
    }

    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_letters(input);
    printf("%s\n", input);
    return 0;
}