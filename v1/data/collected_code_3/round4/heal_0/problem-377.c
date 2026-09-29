#include <stdio.h>
#include <string.h>

void remove_char(char *str, char c) {
    int i = 0;
    int j = 0;
    while (str[i]) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[100];
    char c;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    printf("Enter the character to remove: ");
    scanf("%c", &c);

    remove_char(str, c);

    printf("Result: %s\n", str);

    return 0;
}