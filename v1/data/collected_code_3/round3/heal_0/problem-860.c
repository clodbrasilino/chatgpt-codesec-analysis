#include <stdio.h>
#include <regex.h>
#include <string.h>

int check_alphanumeric_end(char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "[a-zA-Z0-9]$", 0);
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
    char str1[] = "HelloWorld1";
    char str2[] = "HelloWorld!";
    printf("%s ends with alphanumeric: %s\n", str1, check_alphanumeric_end(str1) ? "Yes" : "No");
    printf("%s ends with alphanumeric: %s\n", str2, check_alphanumeric_end(str2) ? "Yes" : "No");
    return 0;
}