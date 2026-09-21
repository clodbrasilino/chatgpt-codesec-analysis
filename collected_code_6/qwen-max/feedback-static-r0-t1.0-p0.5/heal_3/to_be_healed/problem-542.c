#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int reti;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     */
    char *ptr = str, *end = str + strlen(str);

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED)) {
        return;
    }

    /* Possible weaknesses found:
     *  Although the value stored to 'reti' is used in the enclosing expression, the value is never actually read from 'reti' [deadcode.DeadStores]
     */
    while ((reti = regexec(&regex, ptr, 1, pmatch, 0)) == 0) {
        size_t len = end - (ptr + pmatch[0].rm_eo);
        memmove(ptr + 1, ptr + pmatch[0].rm_eo, len + 1);
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