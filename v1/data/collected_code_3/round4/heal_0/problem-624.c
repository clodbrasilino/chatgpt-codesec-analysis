#include <stdio.h>
#include <ctype.h>
#include <string.h>

void convertToUpperCase(char *str) {
    for(int i = 0; str[i]; i++){
        str[i] = toupper(str[i]);
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    convertToUpperCase(str);
    printf("Upper case string: %s", str);
    return 0;
}