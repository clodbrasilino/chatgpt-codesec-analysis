#include <stdio.h>
#include <regex.h>

void splitString(char* str) {
    regex_t regex;
    char* pattern = "[A-Z]";
    int reti;

    reti = regcomp(&regex, pattern, 0);
    if (reti) {
        printf("Could not compile regex\n");
        return;
    }

    char* token = strtok(str, pattern);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, pattern);
    }

    regfree(&regex);
}

int main() {
    char str[] = "SplitThisString";
    splitString(str);
    return 0;
}