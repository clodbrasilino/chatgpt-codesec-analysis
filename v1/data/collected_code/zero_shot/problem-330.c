#include <stdio.h>
#include <regex.h>

void findWords(char *str) {
    regex_t regex;
    regmatch_t matches[1];
    int reti;

    regcomp(&regex, "\\b\\w{3,5}\\b", REG_EXTENDED);

    while ((reti = regexec(&regex, str, 1, matches, 0)) != REG_NOMATCH) {
        if (reti == 0) {
            for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
                printf("%c", str[i]);
            }
            printf("\n");
            str += matches[0].rm_eo;
        }
    }

    regfree(&regex);
}

int main() {
    char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    findWords(str);

    return 0;
}