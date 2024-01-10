#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 101

void removeWhitespace(char *str) {
    if (!str) return;

    int i = 0, j = 0;
    while(str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        ++i;
    }
    str[j] = '\0';
}

int main() {
    char str[MAX_LENGTH] = {0};

    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin)) {
        char* newline = strchr(str, '\n');
        if (newline) 
           *newline = '\0';
    }

    printf("Before removing whitespaces: %s\n", str);

    removeWhitespace(str);

    printf("After removing whitespaces: %s\n", str);

    return 0;
}