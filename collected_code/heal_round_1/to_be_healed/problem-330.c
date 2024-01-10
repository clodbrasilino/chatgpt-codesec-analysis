#include <stdio.h>
#include <regex.h>

void findWords(char *str) {
    regex_t regex;
    regmatch_t matches[1];
    int reti;

    regcomp(&regex, "\\b\\w{3,5}\\b", REG_EXTENDED);

    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while ((reti = regexec(&regex, str, 1, matches, 0)) != REG_NOMATCH) {
        if (reti == 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
             */
            for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
                printf("%c", str[i]);
            }
            printf("\n");
            /* Possible weaknesses found:
             *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
             */
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