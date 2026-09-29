#include<stdio.h>
#include<string.h>

#define STRING_MAX_LENGTH 101

char findCharacter(char* str, int length) {
    char result = '\0';
    if(str != NULL){
        for(int i = 0; i < length && str[i] != '\0'; i++) {
            result += str[i];
        }
    }
    return result;
}

int main() {
    char str[STRING_MAX_LENGTH] = {0};
    printf("Enter a string: ");
    if(fgets(str, STRING_MAX_LENGTH, stdin) != NULL) {
        int length = strlen(str);
        str[strcspn(str, "\n")] = '\0';
        char character = findCharacter(str, length);
        printf("Character made by adding all the characters of the given string: %c\n", character);
    } else {
        fprintf(stderr, "Failed to read the line\n");
    }
    return 0;
}