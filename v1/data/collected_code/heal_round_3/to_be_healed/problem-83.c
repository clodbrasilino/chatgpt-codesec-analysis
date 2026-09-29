#include<stdio.h>

const char findCharacter(const char* str, int length) {
    char result = '\0';
    int i = 0;
    
    while(i < length && str[i] != '\0') {
        result += str[i];
        i++;
    }
    
    return result;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[101] = {0};
    printf("Enter a string: ");
    fgets(str, 101, stdin);
    
    char character = findCharacter(str, 101);
    printf("Character made by adding all the characters of the given string: %c\n", character);
    
    return 0;
}