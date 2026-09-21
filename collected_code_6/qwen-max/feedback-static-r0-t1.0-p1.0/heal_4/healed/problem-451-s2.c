#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_whitespaces(char *str) {
    regex_t re;
    regmatch_t pmatch[2];
    char pattern[] = "\\s";

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NEWLINE) == 0) {
        size_t len;
        while (1) {
            len = strlen(str);
            if (regexec(&re, str, 2, pmatch, 0) != 0) break;
            size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
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