#include <stdio.h>
#include <regex.h>
#include <string.h>

int find_sequence(char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[a-z_]*$", 0);
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
    char str[] = "this_is_a_test";
    int result = find_sequence(str);
    if (result == 0) {
        printf("Match found\n");
    } else {
        printf("Match not found\n");
    }
    return 0;
}