#include <stdio.h>
#include <string.h>

void removeChar(char *str, char c) {
    int index = 0;
    int i;
    for (i = 0; str[i]; i++)
        if (str[i] != c)
            str[index++] = str[i];    
    str[index] = '\0';
}

int main() {
    char str[100];
    char c;
    
    printf("Enter a string: ");
    fgets(str, sizeof str, stdin);
    str[strcspn(str, "\n")] = '\0';

    printf("Enter character to be removed: ");
    scanf(" %c", &c);

    removeChar(str, c);

    printf("Resultant string: %s\n", str);
    return 0;
}