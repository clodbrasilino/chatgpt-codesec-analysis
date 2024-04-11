#include <stdio.h>
#include <regex.h>
#include <string.h>

int isEndsWithAlphanumeric(char *str) {
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

    if (isEndsWithAlphanumeric(str1)) {
        printf("String ends with alphanumeric character\n");
    } else {
        printf("String does not end with alphanumeric character\n");
    }

    if (isEndsWithAlphanumeric(str2)) {
        printf("String ends with alphanumeric character\n");
    } else {
        printf("String does not end with alphanumeric character\n");
    }

    return 0;
}