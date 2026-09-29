#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void addSpaces(char *str) {
    regex_t regex;
    char *newStr = (char *) malloc(sizeof(char) * strlen(str) * 2 + 1);
    int i, j = 0;

    if (newStr == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        exit(1);
    }

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