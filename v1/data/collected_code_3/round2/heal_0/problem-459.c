#include <stdio.h>
#include <string.h>
#include <regex.h>

char* remove_uppercase_substrings(char* str) {
    regex_t regex;
    regcomp(&regex, "[A-Z]+", 0);
    regmatch_t pmatch[1];
    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        int len = strlen(str);
        memmove(&str[pmatch[0].rm_so], &str[pmatch[0].rm_eo], len - pmatch[0].rm_eo + 1);
    }
    regfree(&regex);
    return str;
}

int main() {
    char str[] = "HelloWorld";
    printf("%s\n", remove_uppercase_substrings(str));
    return 0;
}