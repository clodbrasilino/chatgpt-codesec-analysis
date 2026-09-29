#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int status, len = strlen(str);
    /* Possible weaknesses found:
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     */
    char *ptr = str, *end = str + len + 1;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED)) {
        return;
    }

    /* Possible weaknesses found:
     *  Although the value stored to 'status' is used in the enclosing expression, the value is never actually read from 'status' [deadcode.DeadStores]
     */
    while ((status = regexec(&regex, ptr, 1, pmatch, 0)) == 0) {
        memmove(ptr + 1, ptr + pmatch[0].rm_eo, end - (ptr + pmatch[0].rm_eo));
        *ptr = ':';
        ptr += pmatch[0].rm_eo - pmatch[0].rm_so;
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len -= pmatch[0].rm_eo - pmatch[0].rm_so - 1;
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World. This is a test string.";
    replace_chars(input);
    printf("%s\n", input);
    return 0;
}