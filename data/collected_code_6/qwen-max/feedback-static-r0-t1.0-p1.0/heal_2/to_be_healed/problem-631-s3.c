#include <stdio.h>
#include <string.h>
#include <regex.h>

void swap_whitespace_underscore(char *str) {
    regex_t regex;
    regmatch_t pmatch[2];
    int match;

    if (regcomp(&regex, "[\\s_]", REG_EXTENDED) != 0) {
        return;
    }

    char *ptr = str;
    /* Possible weaknesses found:
     *  Although the value stored to 'match' is used in the enclosing expression, the value is never actually read from 'match' [deadcode.DeadStores]
     */
    while ((match = regexec(&regex, ptr, 2, pmatch, 0)) == 0) {
        if (pmatch[0].rm_so == pmatch[0].rm_eo) {
            break;
        }
        if (ptr[pmatch[0].rm_so] == ' ') {
            ptr[pmatch[0].rm_so] = '_';
        } else if (ptr[pmatch[0].rm_so] == '_') {
            ptr[pmatch[0].rm_so] = ' ';
        }
        ptr += pmatch[0].rm_eo;
    }

    regfree(&regex);
}

int main() {
    char str[] = "This is a test_string";
    swap_whitespace_underscore(str);
    printf("%s\n", str);
    return 0;
}