#include <stdio.h>
#include <string.h>
#include <ctype.h>

void strToLower(char *str) {
    if (str == NULL) return;
    for (int i = 0; str[i]; i++){
        str[i] = tolower((unsigned char)str[i]);
    }
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;

    strToLower(str);

    printf("Lowercase string: %s\n", str);

    return 0;
}