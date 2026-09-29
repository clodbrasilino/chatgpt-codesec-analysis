#include <stdio.h>
#include <string.h>

void removeChar(char *str, char c) {
    int i, j = 0, n = strlen(str);
    char temp[n];
    for (i = 0; i < n; i++) {
        if (str[i] != c) {
            temp[j++] = str[i];
        } else if (str[i] == c && str[n - 1] != c) {
            temp[j++] = str[i];
        }
        if (str[i] == c) {
            n--;
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

int main() {
    char str[100];
    char c;
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';
    printf("Enter a character to remove: ");
    scanf("%c", &c);
    removeChar(str, c);
    printf("Resultant string: %s\n", str);
    return 0;
}