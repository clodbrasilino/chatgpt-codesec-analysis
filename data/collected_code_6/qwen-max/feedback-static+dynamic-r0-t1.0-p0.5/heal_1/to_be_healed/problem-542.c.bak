#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int reti;
    char *ptr = str;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        return;
    }

    /* Possible weaknesses found:
     *  Although the value stored to 'reti' is used in the enclosing expression, the value is never actually read from 'reti' [deadcode.DeadStores]
     */
    while ((reti = regexec(&regex, ptr, 1, pmatch, 0)) == 0) {
        memmove(ptr + 1, ptr + pmatch[0].rm_eo, strlen(ptr + pmatch[0].rm_eo) + 1);
        *ptr = ':';
        ptr += 2;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}