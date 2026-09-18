#include <stdio.h>
#include <regex.h>
#include <string.h>

int vowel_starting(char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[AEIOUaeiou]", 0);
    if (reti) {
        printf("Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    if (!reti)
        return 0;
    else if (reti == REG_NOMATCH)
        return 1;
    else {
        perror("Regex match failed");
        return 1;
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0'; // remove the newline from fgets

    int result = vowel_starting(str);
    if(result == 0) {
        printf("The string starts with a vowel.\n");
    } else {
        printf("The string does not start with a vowel.\n");
    }

    return 0;
}