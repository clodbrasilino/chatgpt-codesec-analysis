#include <stdio.h>
#include <string.h>
#include <regex.h>

void add_spaces(char *str) {
    regex_t regex;
    regmatch_t match[2];
    char new_str[256] = "";
    char *ptr = str;

    regcomp(&regex, "[A-Z][a-z]*", REG_EXTENDED);

    while (regexec(&regex, ptr, 2, match, 0) == 0) {
        strncat(new_str, ptr, match[0].rm_so);
        strcat(new_str, " ");
        strncat(new_str, ptr + match[0].rm_so, match[0].rm_eo - match[0].rm_so);
        ptr += match[0].rm_eo;
    }

    strcat(new_str, ptr);
    strcpy(str, new_str);

    regfree(&regex);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    add_spaces(str);
    printf("%s\n", str);
    return 0;
}