#include <stdio.h>
#include <string.h>

void replaceChars(char* str) {
    int length = strlen(str);

    for(int i = 0; i < length; i++) {
        if(str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main() {
    char str[100];

    printf("Enter a string: \n");
    fgets(str, 100, stdin);

    replaceChars(str);

    printf("Updated string: \n%s", str);

    return 0;
}