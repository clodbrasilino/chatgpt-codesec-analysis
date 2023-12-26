#include <stdio.h>
#include <ctype.h>
#define MAX_LENGTH 101

void camelToSnake(char* str) {
    int i, j;
    char c;

    for(i = 0, j = 0; str[i] != '\0'; i++, j++) {
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
    
    if (str[strlen(str)-1] == '\n')
      str[strlen(str)-1] = '\0';

    camelToSnake(str);

    printf("The snake case string is: %s\n", str);

    return 0;
}