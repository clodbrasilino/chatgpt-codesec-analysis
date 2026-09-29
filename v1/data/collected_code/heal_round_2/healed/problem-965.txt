#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 101

void camelToSnake(char* str) {
    int i, j;
    char c;

    for(i = 0, j = 0; i < strlen(str); i++, j++) {
        c = str[i];

        if(isupper(c)) {
            str[j] = '_';
            str[++j] = tolower(c);
        } else {
            str[j] = c;
        }
    }
    str[j] = '\0';
}

int main() {
    char str[MAX_LENGTH];

    printf("Enter a camel case string: ");
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = '\0';

    camelToSnake(str);

    printf("The snake case string is: %s\n", str);

    return 0;
}