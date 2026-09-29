#include <stdio.h>
#include <string.h>
#include <regex.h>

int checkSameCharStartEnd(char *str) {
    regex_t regex;
    int reti;
    char pattern[50];

    sprintf(pattern, "^%c.*%c$", str[0], str[strlen(str) - 1]);

    reti = regcomp(&regex, pattern, 0);
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
        regerror(reti, &regex, pattern, sizeof(pattern));
        fprintf(stderr, "Regex match failed: %s\n", pattern);
        return 0;
    }

    regfree(&regex);
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    if (checkSameCharStartEnd(str)) {
        printf("The string starts and ends with the same character.\n");
    } else {
        printf("The string does not start and end with the same character.\n");
    }

    return 0;
}