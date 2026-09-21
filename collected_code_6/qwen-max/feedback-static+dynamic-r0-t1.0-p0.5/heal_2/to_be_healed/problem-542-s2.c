#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    /* Possible weaknesses found:
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     */
    char *ptr = str, *end = str + len;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    while (regexec(&regex, ptr, 1, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        memmove(ptr + 1, ptr + match_len, end - ptr - match_len + 1);
        *ptr = ':';
        ptr += match_len + 1;
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World. This is a test string.";
    replace_chars(input);
    printf("%s\n", input);
    return 0;
}