#include <stdio.h>
#include <regex.h>
#include <string.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) return;

    for (size_t i = 0; ; i++) {
        int rc = regexec(&regex, str + i, 1, pmatch, 0);
        if (rc == REG_NOMATCH) break;
        if (rc != 0) {
            regfree(&regex);
            return;
        }
        size_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
        memmove(str + i + 1, str + i + len, strlen(str + i + len) + 1);
        str[i] = ':';
    }
    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}