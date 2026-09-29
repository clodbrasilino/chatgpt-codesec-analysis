#include <stdio.h>
#include <string.h>
#include <regex.h>

int check_decimal_precision(const char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[0-9]*\\.[0-9]{2}$", REG_EXTENDED);
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
    char *test1 = "123.45";
    char *test2 = "123.4";
    char *test3 = "123.456";

    printf("%s --> %s\n", test1, check_decimal_precision(test1) ? "Valid" : "Invalid");
    printf("%s --> %s\n", test2, check_decimal_precision(test2) ? "Valid" : "Invalid");
    printf("%s --> %s\n", test3, check_decimal_precision(test3) ? "Valid" : "Invalid");

    return 0;
}