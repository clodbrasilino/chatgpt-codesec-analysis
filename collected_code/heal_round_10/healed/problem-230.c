#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define SIZE 101
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void replaceSpaces(char *str, const char ch, size_t max_size) {
    size_t i;
    for(i = 0; i < max_size && i < SIZE - 1; i++) {
        if(str[i] == ' ') {
            str[i] = ch;
        }
    }
    str[i] = '\0';
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
    if(scanf(" %c", &ch) != 1) {
        printf("Error reading character.\n");
        return 1;
    }

    int c;
    while((c = getchar()) != '\n' && c != EOF);

    size_t strLen = strnlen(str, sizeof(str));
    
    if(strLen) {
        replaceSpaces(str, ch, strLen);
    }

    printf("Modified string: %s\n", str);

    return 0;
}