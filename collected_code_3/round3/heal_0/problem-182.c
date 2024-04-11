#include <stdio.h>
#include <regex.h>

void findCharacters(char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "[A-Z]", 0);
    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        printf("String contains uppercase character.\n");
    }

    reti = regcomp(&regex, "[a-z]", 0);
    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        printf("String contains lowercase character.\n");
    }

    reti = regcomp(&regex, "[0-9]", 0);
    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        printf("String contains numeric value.\n");
    }

    reti = regcomp(&regex, "[^a-zA-Z0-9]", 0);
    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        printf("String contains special character.\n");
    }

    regfree(&regex);
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    findCharacters(str);
    return 0;
}