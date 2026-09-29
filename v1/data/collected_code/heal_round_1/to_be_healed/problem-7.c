#include <stdio.h>
#include <regex.h>

void findLongWords(char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "\\b\\w{4,}\\b", REG_EXTENDED);
    if (ret != 0) {
        printf("Could not compile regex\n");
        return;
    }

    regmatch_t matches[1];
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        /* Possible weaknesses found:
         *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
         */
        for (int i = matches[0].rm_so; i <= matches[0].rm_eo; i++) {
            putchar(str[i]);
        }
        putchar('\n');
        /* Possible weaknesses found:
         *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
         */
        str += matches[0].rm_eo;
    }
    regfree(&regex);
}

int main() {
    char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    findLongWords(str);

    return 0;
}