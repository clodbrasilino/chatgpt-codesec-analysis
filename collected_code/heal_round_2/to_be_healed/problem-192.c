#include <stdio.h>
#include <ctype.h>

int checkString(const char* str) {
    int hasLetter = 0;
    int hasNumber = 0;
    
    for(int i = 0; str[i] != '\0'; i++) {
        if(isalpha((unsigned char)str[i]))
            hasLetter = 1;
        else if(isdigit((unsigned char)str[i]))
            hasNumber = 1;
        
        if(hasLetter && hasNumber)
            return 1;
    }
    
    return 0;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[101];
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *   It's unclear if the %s limit in the format string is small enough  (CWE-120). Check that the limit is sufficiently small, or use a different  input function.
     */
    scanf("%100s", str);
    
    if(checkString(str))
        printf("The string has at least one letter and one number.\n");
    else
        printf("The string does not have at least one letter and one number.\n");
    
    return 0;
}