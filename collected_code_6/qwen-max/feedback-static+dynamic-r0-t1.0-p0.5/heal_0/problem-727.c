#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void sanitize_string(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *p = str;
    int len, i;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (*p) {
        if (regexec(&regex, p, 1, match, 0) == 0) {
            len = strlen(p + match[0].rm_eo);
            memmove(p + match[0].rm_so, p + match[0].rm_eo, len + 1);
        } else {
            p++;
        }
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    sanitize_string(input);
    printf("%s\n", input);
    return 0;
}