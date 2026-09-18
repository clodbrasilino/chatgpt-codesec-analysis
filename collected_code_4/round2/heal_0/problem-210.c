#include <stdio.h>
#include <string.h>
#include <regex.h>

int checkString(char *str) {
    regex_t regex;
    int rc;

    rc = regcomp(&regex, "^[a-zA-Z0-9]*$", REG_EXTENDED);

    if (rc) {
        printf("Could not compile regex\n");
        return 0;
    }

    rc = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (!rc) {
        return 1;
    } else if (rc == REG_NOMATCH) {
        return 0;
    } else {
        printf("Regex match failed\n");
        return 0;
    }

}

int main() {
    char str[100];
    printf("Enter a string: \n");
    scanf("%s", str);

    if (checkString(str)) {
        printf("The entered string contains only a-z, A-Z, 0-9.\n");
    } else {
        printf("The entered string has characters other than a-z, A-Z, 0-9.\n");
    }

    return 0;
}