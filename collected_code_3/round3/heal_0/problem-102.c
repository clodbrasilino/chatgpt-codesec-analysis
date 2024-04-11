#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snakeToCamel(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] == '_') {
            str[j] = toupper(str[i + 1]);
            i++;
        } else {
            str[j] = str[i];
        }
        i++;
        j++;
    }
    str[j] = '\0';
    return str;
}

int main() {
    char str[100];
    printf("Enter a snake case string: ");
    scanf("%s", str);
    printf("Camel case string: %s", snakeToCamel(str));
    return 0;
}