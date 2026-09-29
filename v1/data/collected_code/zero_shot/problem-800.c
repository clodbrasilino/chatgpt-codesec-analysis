#include<stdio.h>

void removeWhitespace(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    printf("Before removing whitespaces: %s\n", str);
    removeWhitespace(str);
    printf("After removing whitespaces: %s\n", str);
    return 0;
}