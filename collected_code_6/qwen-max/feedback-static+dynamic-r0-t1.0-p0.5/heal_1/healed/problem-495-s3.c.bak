#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "[a-z]+";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    while (1) {
        int reti = regexec(&regex, str, 1, match, 0);
        if (reti == REG_NOMATCH) {
            break;
        } else if (reti != 0) {
            regfree(&regex);
            return;
        }

        for (int i = match[0].rm_eo; i <= strlen(str); i++) {
            str[i - (match[0].rm_eo - match[0].rm_so)] = str[i];
        }
        str[strlen(str) - (match[0].rm_eo - match[0].rm_so)] = '\0';
    }

    regfree(&regex);
}

int main() {
    char input[] = "HeLlO WoRlD";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}