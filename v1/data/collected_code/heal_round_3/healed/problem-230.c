#include <stdio.h>
#include <string.h>

#define SIZE 101

void replaceSpaces(char *str, const char ch, size_t max_size) {
    for (size_t i = 0; i < max_size && str[i] != '\0'; i++) {
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
    str[strcspn(str, "\n")] = '\0';
    
    printf("Enter the character to replace spaces with: ");
    while ((getchar()) != '\n');
    scanf("%c", &ch);
    replaceSpaces(str, ch, sizeof(str));
    printf("Modified string: %s\n", str);
    return 0;
}