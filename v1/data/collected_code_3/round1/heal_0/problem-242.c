#include <stdio.h>
#include <string.h>

int countCharacters(char* str) {
    int count = 0;
    while(*str != '\0') {
        count++;
        str++;
    }
    return count;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';
    printf("Total characters: %d", countCharacters(str));
    return 0;
}