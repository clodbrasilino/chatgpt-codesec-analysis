#include <stdio.h>
#include <regex.h>

int starts_with_vowel(char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[aeiouAEIOU]", 0);
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
    char str[] = "apple";
    if (starts_with_vowel(str)) {
        printf("The string starts with a vowel.\n");
    } else {
        printf("The string does not start with a vowel.\n");
    }
    return 0;
}