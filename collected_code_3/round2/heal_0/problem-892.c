#include <stdio.h>
#include <string.h>

void removeMultipleSpaces(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ' || (str[i] == ' ' && str[i+1] != ' '))
            str[count++] = str[i];
    str[count] = '\0';
}

int main() {
    char str[] = "C   programming   language";
    removeMultipleSpaces(str);
    printf("%s", str);
    return 0;
}