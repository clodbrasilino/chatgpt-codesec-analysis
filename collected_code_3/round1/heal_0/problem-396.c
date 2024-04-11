#include <stdio.h>
#include <string.h>
#include <regex.h>

int check_same_char(char *str) {
    regex_t regex;
    char pattern[50];
    sprintf(pattern, "^%c.*%c$", str[0], str[strlen(str) - 1]);

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 0;
    }

    if (regexec(&regex, str, 0, NULL, 0) == 0) {
        regfree(&regex);
        return 1;
    } else {
        regfree(&regex);
        return 0;
    }
}

int main() {
    char str[] = "helloh";
    if (check_same_char(str)) {
        printf("The string starts and ends with the same character.\n");
    } else {
        printf("The string does not start and end with the same character.\n");
    }
    return 0;
}