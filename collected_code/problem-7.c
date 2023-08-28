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
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        for (int i = matches[0].rm_so; i <= matches[0].rm_eo; i++) {
            putchar(str[i]);
        }
        putchar('\n');
        str += matches[0].rm_eo;
    }
    regfree(&regex);
}

int main() {
    char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    findLongWords(str);

    return 0;
}