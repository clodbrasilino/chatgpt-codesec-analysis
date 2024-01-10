#include <stdio.h>
#include <regex.h>

void findWords(const char *str) {
    regex_t regex;
    regmatch_t matches[1];
    int reti;

    regcomp(&regex, "\\b\\w{3,5}\\b", REG_EXTENDED);

    const char *newStr = str;
    while ((reti = regexec(&regex, newStr, 1, matches, 0)) != REG_NOMATCH) {
        if (reti == 0) {
            for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
                printf("%c", newStr[i]);
            }
            printf("\n");
            newStr += matches[0].rm_eo;
        }
    }

    regfree(&regex);
}

int main() {
    char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    findWords(str);

    return 0;
}