#include <stdio.h>
#include <string.h>

void removeOccurrences(char * str, char c) {
    int i, j = 0, len;
    len = strlen(str);

    for(i = 0; i < len; i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        } else if (str[i] == c && i == len - 1) {
            str[j++] = '\0';
        }
    }
    str[j] = '\0';
}

int main() {
    char str[100];
    char c;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    printf("Enter a character: ");
    scanf(" %c", &c);

    removeOccurrences(str, c);

    printf("Resultant string is: %s", str);

    return 0;
}