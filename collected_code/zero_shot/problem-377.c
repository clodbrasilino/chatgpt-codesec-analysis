#include<stdio.h>

void removeChar(char* str, char c) {
    int count = 0;
    int i;
    
    for (i = 0; str[i]; i++) {
        if (str[i] != c) {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

int main() {
    char str[100];
    char c;

    printf("Enter a string: ");
    scanf("%s", str);

    printf("Enter the character to remove: ");
    scanf(" %c", &c);

    removeChar(str, c);

    printf("String after removing character '%c': %s\n", c, str);

    return 0;
}