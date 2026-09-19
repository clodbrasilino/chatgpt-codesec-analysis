#include <stdio.h>
#include <regex.h>
#include <string.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char buffer[256];
    int rc, i = 0;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        return;
    }

    /* Possible weaknesses found:
     *  Although the value stored to 'rc' is used in the enclosing expression, the value is never actually read from 'rc' [deadcode.DeadStores]
     */
    while ((rc = regexec(&regex, str + i, 1, pmatch, 0)) == 0) {
        strncpy(buffer, str + i, pmatch[0].rm_so);
        buffer[pmatch[0].rm_so] = ':';
        buffer[pmatch[0].rm_so + 1] = '\0';
        strcat(buffer, str + i + pmatch[0].rm_eo);
        strcpy(str + i, buffer);
        i += pmatch[0].rm_so + 1;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}