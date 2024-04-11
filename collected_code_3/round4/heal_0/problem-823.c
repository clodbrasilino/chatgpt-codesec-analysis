#include <stdio.h>
#include <string.h>
#include <regex.h>

int starts_with_substring(const char *str, const char *sub) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, sub, 0);
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
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }

    regfree(&regex);
}

int main() {
    char *str = "Hello, World!";
    char *sub = "Hello";
    if (starts_with_substring(str, sub)) {
        printf("The string starts with the substring.\n");
    } else {
        printf("The string does not start with the substring.\n");
    }
    return 0;
}