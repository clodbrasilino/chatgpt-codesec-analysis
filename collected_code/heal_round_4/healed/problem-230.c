#include <stdio.h>
#include <string.h>

#define SIZE 101

void replaceSpaces(char *str, const char ch, size_t max_size) {
    size_t str_len = strlen(str);
    size_t count = str_len > max_size ? max_size : str_len;
    for (size_t i = 0; i < count; i++) {
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
    replaceSpaces(str, ch, strlen(str));
    printf("Modified string: %s\n", str);
    return 0;
}