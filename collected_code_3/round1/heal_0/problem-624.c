#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toUpperCase(char *str) {
    for(int i = 0; str[i]; i++){
        str[i] = toupper(str[i]);
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    toUpperCase(str);
    printf("String in upper case: %s", str);
    return 0;
}