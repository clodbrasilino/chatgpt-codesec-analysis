#include <stdio.h>
#include <string.h>
#include <regex.h>

void addSpaces(char *str) {
    regex_t regex;
    char *newStr = malloc(strlen(str) * 2);
    int i, j = 0;

    regcomp(&regex, "[A-Z]", 0);

    for(i = 0; i < strlen(str); i++) {
        if(regexec(&regex, &str[i], 0, NULL, 0) == 0 && i != 0) {
            newStr[j++] = ' ';
        }
        newStr[j++] = str[i];
    }

    newStr[j] = '\0';
    strcpy(str, newStr);
    free(newStr);
    regfree(&regex);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    addSpaces(str);
    printf("%s\n", str);
    return 0;
}