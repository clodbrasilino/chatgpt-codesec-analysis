#include <stdio.h>
#include <regex.h>
#include <string.h>

int isAlphanumeric(char *str) {
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
        regerror(reti, &regex, str, sizeof(str));
        fprintf(stderr, "Regex match failed: %s\n", str);
        return 0;
    }

    regfree(&regex);
}

int main() {
    char str1[] = "HelloWorld123";
    char str2[] = "HelloWorld!@#";

    if (isAlphanumeric(str1)) {
        printf("String 1 ends with alphanumeric character\n");
    } else {
        printf("String 1 does not end with alphanumeric character\n");
    }

    if (isAlphanumeric(str2)) {
        printf("String 2 ends with alphanumeric character\n");
    } else {
        printf("String 2 does not end with alphanumeric character\n");
    }

    return 0;
}