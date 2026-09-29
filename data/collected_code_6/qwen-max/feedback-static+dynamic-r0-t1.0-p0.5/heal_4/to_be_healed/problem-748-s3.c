#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void add_spaces_between_capital_letters(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "([a-z])([A-Z])";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    int pos = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    while (regexec(&regex, str + pos, 1, match, 0) == 0 && pos <= len) {
        int start = pos + match[0].rm_so;
        int end = pos + match[0].rm_eo;
        memmove(str + start + 1, str + start, end - start + 1);
        str[start] = ' ';
        for (int i = len; i > start; i--) {
            str[i + 1] = str[i];
        }
        str[start + 1] = ' ';
        len++;
        str[len] = '\0';
        pos = start + 2;
    }

    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_letters(input);
    printf("%s\n", input);
    return 0;
}