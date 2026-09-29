#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool hasLetterAndNumber(const char* str) {
    bool hasLetter = false;
    bool hasDigit = false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            hasLetter = true;
        } else if (isdigit(str[i])) {
            hasDigit = true;
        }
        if(hasLetter && hasDigit){
            return true;
        }
    }
    return false;
}

int main() {
    const char* str = "Hello1";
    bool result = hasLetterAndNumber(str);
    if(result){
        printf("The string has at least one letter and one number.\n");
    }else{
        printf("The string doesn't have at least one letter and one number.\n");
    }
    return 0;
}