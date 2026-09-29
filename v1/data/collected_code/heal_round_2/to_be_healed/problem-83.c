#include<stdio.h>

const char findCharacter(const char* str) {
    char result = '\0';
    int i = 0;
    
    while(str[i] != '\0') {
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
    /* Possible weaknesses found:
     *   It's unclear if the %s limit in the format string is small enough  (CWE-120). Check that the limit is sufficiently small, or use a different  input function.
     */
    scanf("%100s", str);
    
    char character = findCharacter(str);
    printf("Character made by adding all the characters of the given string: %c\n", character);
    
    return 0;
}