#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_whitespaces(char *str) {
    regex_t re;
    regmatch_t pmatch[1];
    char pattern[] = "\\s";

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NEWLINE) == 0) {
        while (1) {
            size_t len = strnlen(str, 1024);
            if (regexec(&re, str, 1, pmatch, 0) != 0) break;
            memmove(str + pmatch[0].rm_so, str + pmatch[0].rm_eo, len - pmatch[0].rm_eo + 1);
        }
        regfree(&re);
    }
}

int main() {
    char input[] = "  Hello   World  ";
    remove_whitespaces(input);
    printf("%s\n", input);
    return 0;
}