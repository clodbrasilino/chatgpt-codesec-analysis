#include <stdio.h>
#include <regex.h>
#include <string.h>

int find_pattern(char* str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[a-z]+(_[a-z]+)*$", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        return 0;
    } else if (reti == REG_NOMATCH) {
        return 1;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    int result = find_pattern(str);
    if (result == 0) {
        printf("Pattern found!\n");
    } else {
        printf("Pattern not found!\n");
    }

    return 0;
}