#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

void remove_uppercase_substrings(char *str) {
    regex_t regex;
    regcomp(&regex, "[A-Z]+", 0);
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    while (regexec(&regex, str, nmatch, pmatch, 0) == 0) {
        for(int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++)
            str[i] = ' ';
    }
    regfree(&regex);
}

int main() {
    char str[] = "HelloWorld";
    remove_uppercase_substrings(str);
    printf("%s\n", str);
    return 0;
}