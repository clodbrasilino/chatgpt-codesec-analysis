#include<stdio.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

const char findCharacter(const char* str, int length) {
    char result = '\0';
    int i = 0;
    while(str[i] != '\0' && i<length) {
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
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     */
    int length = strlen(str);
    
    if(length<=100){
        char character = findCharacter(str, length);
        printf("Character made by adding all the characters of the given string: %c\n", character);
    }
    else printf("Invalid input\n");
    return 0;
}