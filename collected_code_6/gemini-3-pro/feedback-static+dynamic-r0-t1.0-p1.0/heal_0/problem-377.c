#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeCharacter(char *str, char c) {
    if (str == NULL) {
        return;
    }

    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if (str[i] != c) {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

int main(void) {
    char str[] = "Hello World!";
    char target = 'l';

    removeCharacter(str, target);
    printf("%s\n", str);

    return 0;
}