#include <stdio.h>
#include <string.h>
#include <regex.h>

int match_string(char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "a.*b$", 0);
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
    char str[] = "abc";
    int result = match_string(str);
    if (result == 0) {
        printf("Match found\n");
    } else {
        printf("Match not found\n");
    }
    return 0;
}