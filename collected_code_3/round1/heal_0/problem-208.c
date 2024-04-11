#include <stdio.h>
#include <regex.h>

int check_decimal(char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[0-9]*\\.?[0-9]{0,2}$", 0);
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
    char str[100];
    printf("Enter a decimal number: ");
    scanf("%s", str);

    if (check_decimal(str)) {
        printf("Valid decimal with a precision of 2\n");
    } else {
        printf("Invalid decimal\n");
    }

    return 0;
}