#include<stdio.h>

char findCharacter(char* str) {
    char result = '\0';
    int i = 0;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while(str[i] != '\0') {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        result += str[i];
        i++;
    }
    
    return result;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100];
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
    scanf("%s", str);
    
    char character = findCharacter(str);
    printf("Character made by adding all the characters of the given string: %c\n", character);
    
    return 0;
}