#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_with_colon(char *str) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "[ ,.]", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    int i = 0;
    while (str[i]) {
        reti = regexec(&regex, &str[i], 0, NULL, 0);
        if (!reti) {
            str[i] = ':';
        }
        i++;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, world. This is a test string.";
    replace_with_colon(str);
    printf("%s\n", str);
    return 0;
}