#include <stdio.h>
#include <regex.h>
#include <string.h>

int starts_with_vowel(char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[aeiouAEIOU]", 0);
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
    char str1[] = "apple";
    char str2[] = "banana";

    if (starts_with_vowel(str1)) {
        printf("%s starts with a vowel\n", str1);
    } else {
        printf("%s does not start with a vowel\n", str1);
    }

    if (starts_with_vowel(str2)) {
        printf("%s starts with a vowel\n", str2);
    } else {
        printf("%s does not start with a vowel\n", str2);
    }

    return 0;
}