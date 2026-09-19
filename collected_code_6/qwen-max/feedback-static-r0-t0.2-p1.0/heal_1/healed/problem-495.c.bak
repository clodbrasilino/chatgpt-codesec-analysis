#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char *ptr = str;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    while (1) {
        int reti = regexec(&regex, ptr, 1, pmatch, 0);
        if (reti == REG_NOMATCH) break;
        if (reti != 0) { 
            regfree(&regex);
            return;
        }
        memmove(ptr + pmatch[0].rm_so, ptr + pmatch[0].rm_eo, strlen(ptr + pmatch[0].rm_eo) + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt sTrInG wItH lOwErCaSe ChArAcTeRs";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}