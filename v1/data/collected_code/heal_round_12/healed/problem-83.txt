#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
    char* str = (char*)malloc(STRING_MAX_LENGTH * sizeof(char));
    if (str == NULL){
        fprintf(stderr, "Failed to allocate the memory\n");
        return 1;
    }

    printf("Enter a string: ");
    if(fgets(str, STRING_MAX_LENGTH, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        int length = strlen(str) + 1;
        if (length > 1){
            char character = findCharacter(str, length);
            printf("Character made by adding all the characters of the given string: %c\n", character);
        } else {
            fprintf(stderr, "Empty string received\n");
        }
    } else {
        fprintf(stderr, "Failed to read the line\n");
    }

    free(str);
    return 0;
}