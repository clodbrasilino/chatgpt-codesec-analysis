#include <stdio.h>
#include <string.h>

void remove_char(char* str, char c) {
    int i, j = 0, n = strlen(str);
    char new_str[n+1];

    for(i = 0; i < n; i++) {
        if(str[i] != c) {
            new_str[j++] = str[i];
        } else if(str[i] == c && str[n-1] != c) {
            new_str[j++] = str[i];
        }
        if(str[n-1] == c) {
            str[n-1] = '\0';
        }
    }
    new_str[j] = '\0';
    strcpy(str, new_str);
}

int main() {
    char str[100];
    char c;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    printf("Enter a character: ");
    scanf("%c", &c);

    remove_char(str, c);

    printf("New string: %s\n", str);

    return 0;
}