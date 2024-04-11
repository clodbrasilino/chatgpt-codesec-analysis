#include <stdio.h>
#include <string.h>
#include <regex.h>

int startsWithSubstring(const char *str, const char *substr) {
    regex_t regex;
    char pattern[strlen(substr) + 3];
    sprintf(pattern, "^%s", substr);
    int reti = regcomp(&regex, pattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }
    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
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
}

int main() {
    const char *str = "Hello, World!";
    const char *substr = "Hello";
    if (startsWithSubstring(str, substr)) {
        printf("The string starts with the substring\n");
    } else {
        printf("The string does not start with the substring\n");
    }
    return 0;
}