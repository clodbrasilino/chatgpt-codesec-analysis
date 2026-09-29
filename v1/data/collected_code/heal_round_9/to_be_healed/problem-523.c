#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_STR_LENGTH 1024

bool checkString(const char* str, int size) {
    if(str == NULL || size < 1 || size > MAX_STR_LENGTH) {
        return false;
    }
  
    bool hasCapitalLetter = false;
    bool hasLowerCaseLetter = false;
    bool hasNumber = false;
    int i;
    for (i = 0; i < size && str[i] != '\0'; i++) {
        hasCapitalLetter |= isupper((unsigned char)str[i]) != 0;
        hasLowerCaseLetter |= islower((unsigned char)str[i]) != 0;
        hasNumber |= isdigit((unsigned char)str[i]) != 0;

        if (hasCapitalLetter && hasLowerCaseLetter && hasNumber) {
            return true;
        }
    }
    return false;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_STR_LENGTH + 1] = "aB1";
    str[MAX_STR_LENGTH] = '\0';
    int strLength = strnlen(str, sizeof(str) / sizeof(char));

    if(checkString(str, strLength)) {
        printf("String Passed\n");
    }
    else {
        printf("String Failed\n");
    }

    return 0;
}