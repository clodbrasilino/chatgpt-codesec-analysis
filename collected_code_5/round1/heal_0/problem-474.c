#include <stdio.h>
#include <string.h>

void replace_character(char *str, char old_char, char new_char) {
    if (str == NULL) {
        return;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == old_char) {
            str[i] = new_char;
        }
    }
}

int main() {
    char str[100];
    char old_char, new_char;

    printf("Enter a string:\n");
    fgets(str, sizeof(str), stdin);
    printf("Enter the character you want to replace:\n");
    scanf(" %c", &old_char);
    getchar(); // flush newline character
    printf("Enter the new character:\n");
    scanf(" %c", &new_char);

    replace_character(str, old_char, new_char);
    printf("Updated string: %s\n", str);

    return 0;
}