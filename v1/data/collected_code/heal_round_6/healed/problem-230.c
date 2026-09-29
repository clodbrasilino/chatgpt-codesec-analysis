#include <stdio.h>
#include <string.h>

#define SIZE 101

void replaceSpaces(char *str, const char ch, size_t max_size) {
    size_t count = max_size < SIZE ? max_size : SIZE - 1;
    for (size_t i = 0; i < count; i++) {
        if (str[i] == ' ') {
            str[i] = ch;
        }
    }
    str[count] = '\0';
}

int main() {

    char str[SIZE] = "";
    char ch = '\0';
    size_t len = 0;

    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin) != NULL) {
        len = strcspn(str, "\n");
        if(len < sizeof(str)) {
            str[len] = '\0';
        }
    }

    printf("Enter the character to replace spaces with: "); 
    while ((getchar()) != '\n');
    scanf("%c", &ch);

    if(strnlen_s(str, SIZE)) {
        replaceSpaces(str, ch, strlen(str));
    }

    printf("Modified string: %s\n", str);
    return 0;
}