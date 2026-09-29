#include <stdio.h>
#include <ctype.h>

int checkString(char* str) {
    int hasLetter = 0;
    int hasNumber = 0;
    
    for(int i = 0; str[i] != '\0'; i++) {
        if(isalpha(str[i]))
            hasLetter = 1;
        else if(isdigit(str[i]))
            hasNumber = 1;
        
        if(hasLetter && hasNumber)
            return 1;
    }
    
    return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    
    if(checkString(str))
        printf("The string has at least one letter and one number.\n");
    else
        printf("The string does not have at least one letter and one number.\n");
    
    return 0;
}