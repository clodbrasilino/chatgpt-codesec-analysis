#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_lowercase(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *cursor = str;

    regcomp(&regex, "[a-z]+", REG_EXTENDED);

    while (!regexec(&regex, cursor, 1, match, 0)) {
        memmove(cursor + match[0].rm_so, cursor + match[0].rm_eo, strlen(cursor + match[0].rm_eo) + 1);
        cursor += match[0].rm_so;
    }

    regfree(&regex);
}

int main() {
    char str[] = "HelloWorld";
    remove_lowercase(str);
    printf("%s\n", str);
    return 0;
}