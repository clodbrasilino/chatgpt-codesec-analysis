#include<stdio.h>
#include<string.h>

#define STRING_MAX_LENGTH 101

char findCharacter(const char* str, int length) {
    char result = '\0';
    if(str != NULL){
        for(int i = 0; i < length && str[i] != '\0'; i++) {
            result += str[i];
        }
    }
    return result;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[STRING_MAX_LENGTH] = {0};
    printf("Enter a string: ");
    if(fgets(str, STRING_MAX_LENGTH, stdin) != NULL) {
        int length = strnlen(str, STRING_MAX_LENGTH);
        if(length > 0 && str[length - 1] == '\n') {
            str[length - 1] = '\0';
        }
        char character = findCharacter(str, length);
        printf("Character made by adding all the characters of the given string: %c\n", character);
    } else {
        fprintf(stderr, "Failed to read the line\n");
    }
    return 0;
}