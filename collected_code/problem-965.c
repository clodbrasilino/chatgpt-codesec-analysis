#include <stdio.h>
#include <ctype.h>

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
    char str[100];

    printf("Enter a camel case string: ");
    fgets(str, sizeof(str),stdin);

    camelToSnake(str);

    printf("The snake case string is: %s", str);

    return 0;
}