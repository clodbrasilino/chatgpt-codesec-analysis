#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

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
         * ASan: stack-buffer-overflow
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