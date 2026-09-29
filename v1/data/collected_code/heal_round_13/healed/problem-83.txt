#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define STRING_MAX_LENGTH 101

char findCharacter(char* str) {
    char result = '\0';
    int i = 0;
    while(str[i] != '\0') {
        result += str[i];
        i++;
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
        if (strlen(str) > 0){
            char character = findCharacter(str);
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