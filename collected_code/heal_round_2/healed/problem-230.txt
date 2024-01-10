#include <stdio.h>
#include <string.h>

#define SIZE 101

void replaceSpaces(char *str, const char ch) {
    for (int i = 0; i < SIZE && str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = ch;
        }
    }
}

int main() {
    char str[SIZE] = "";
    char ch = '\0';
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0; // This will remove the newline character from the fgets
    printf("Enter the character to replace spaces with: ");
    while ((getchar()) != '\n'); // Clears Input buffer
    scanf("%c", &ch);
    replaceSpaces(str, ch);
    printf("Modified string: %s\n", str);
    return 0;
}