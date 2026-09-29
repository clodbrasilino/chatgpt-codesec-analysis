#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str, size_t len) {
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
        size_t remaining_len = len - (ptr - str);
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        size_t new_len = remaining_len - match_len + 1;
        memmove(ptr + 1, ptr + match_len, new_len);
        *ptr = ':';
        ptr += 2;
        len -= match_len - 1;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    replace_chars(str, strlen(str));
    printf("%s\n", str);
    return 0;
}