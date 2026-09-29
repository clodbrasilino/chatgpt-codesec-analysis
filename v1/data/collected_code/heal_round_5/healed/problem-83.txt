#include<stdio.h>
#include<string.h>

#define STRING_MAX_LENGTH 101

char findCharacter(const char* str, int length) {
    char result = '\0';
    for(int i = 0; i<length && str[i] != '\0'; i++) {
        result += str[i];
    }
    return result;
}

int main() {
    char str[STRING_MAX_LENGTH] = {0};
    printf("Enter a string: ");
    if(fgets(str, STRING_MAX_LENGTH, stdin) != NULL) {
        int length = strnlen(str, STRING_MAX_LENGTH);
        if(length < STRING_MAX_LENGTH && str[length - 1] == '\n') {
            str[length - 1] = '\0';
            char character = findCharacter(str, length - 1);
            printf("Character made by adding all the characters of the given string: %c\n", character);
        }
        else {
            printf("Invalid input\n");
        }
    }
    return 0;
}