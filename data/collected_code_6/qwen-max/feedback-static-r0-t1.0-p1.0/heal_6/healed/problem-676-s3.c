#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_non_alphanumeric(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *p = str;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        size_t len = strlen(p);
        if (len > 0 && p[match[0].rm_eo] != '\0') {
            memmove(p + match[0].rm_so, p + match[0].rm_eo, len - match[0].rm_eo + 1);
        } else {
            p[match[0].rm_so] = '\0';
        }
        p = str;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello! This is a test. @123";
    remove_non_alphanumeric(str);
    printf("%s\n", str);
    return 0;
}