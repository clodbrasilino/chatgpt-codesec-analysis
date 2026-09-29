#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snakeToCamel(char *str) {
    int counter = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '_' && str[i+1] && islower(str[i+1])) {
            str[i] = toupper(str[++i]);
            counter++;
        }
        else {
            str[i-counter] = str[i];
        }
    }
    str[i-counter] = '\0';
    return str;
}

int main() {
    char str[100];
    printf("Enter snake_case string: ");
    scanf("%s", str);
    printf("camelCase string: %s\n", snakeToCamel(str));
    return 0;
}