#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define STRING_MAX_LENGTH 101

char findCharacter(char* str, size_t len) {
    char result = '\0';
    for(size_t i = 0; i < len; i++)
        result += str[i];
    return result;
}

int main() {
    char* str = (char*)calloc(STRING_MAX_LENGTH, sizeof(char)); 
    if (str == NULL){
        fprintf(stderr, "Failed to allocate the memory\n");
        return 1;
    }

    printf("Enter a string: ");
    
    if(fgets(str, STRING_MAX_LENGTH, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0'; 
        size_t len = strlen(str);
        if (len > 0) {
            char character = findCharacter(str, len);
            printf("Character made by adding all characters of the given string: %c\n", character);
        } else {
            fprintf(stderr, "Empty string received\n");
        }
    } else {
        fprintf(stderr, "Failed to read the line\n");
    }

    free(str);
    return 0;
}