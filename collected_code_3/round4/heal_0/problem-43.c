#include <stdio.h>
#include <string.h>
#include <regex.h>

int find_sequence(char *str) {
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

    int result = find_sequence(str);
    if (result == 0) {
        printf("The string matches the pattern.\n");
    } else {
        printf("The string does not match the pattern.\n");
    }

    return 0;
}