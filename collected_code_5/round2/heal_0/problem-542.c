#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void replaceCharWithColon(char *str) {
    int i;
    for(i=0; i<strlen(str); i++) {
        if(str[i] == ' ' || str[i] == ',' || str[i] == '.')
            str[i] = ':';
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';
    replaceCharWithColon(str);
    printf("Modified string: %s", str);
    return 0;
}