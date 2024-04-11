#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void replace_with_colon(char *str) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "[ ,.]", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    while (!reti) {
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
                str[i] = ':';
            }
        }
        reti = regexec(&regex, str, 0, NULL, 0);
    }

    if (reti == REG_NOMATCH) {
        printf("No match\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, world. This is a test string";
    replace_with_colon(str);
    printf("%s\n", str);
    return 0;
}