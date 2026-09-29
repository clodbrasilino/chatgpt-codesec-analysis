#include <stdio.h>
#include <regex.h>
#include <string.h>

int check_same_char(char *str) {
    regex_t regex;
    char pattern[100];
    sprintf(pattern, "^%c.*%c$", str[0], str[strlen(str)-1]);

    int reti = regcomp(&regex, pattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        fprintf(stderr, "Regex match failed\n");
        return 0;
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    if (check_same_char(str)) {
        printf("The string starts and ends with the same character\n");
    } else {
        printf("The string does not start and end with the same character\n");
    }

    return 0;
}