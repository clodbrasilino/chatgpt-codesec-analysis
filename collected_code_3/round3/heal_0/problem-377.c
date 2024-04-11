#include <stdio.h>
#include <string.h>

void removeChar(char *str, char remove) {
    int i = 0;
    int j = 0;
    while(str[i]) {
        if(str[i] != remove) {
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
    printf("Enter character to remove: ");
    scanf("%c", &c);
    removeChar(str, c);
    printf("Modified string: %s", str);
    return 0;
}