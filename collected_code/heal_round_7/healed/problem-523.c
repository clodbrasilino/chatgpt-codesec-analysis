#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_STR_LENGTH 1024

bool checkString(const char* str, int size) {
    if(str == NULL || size <= 0 || size > MAX_STR_LENGTH) {
        return false;
    }
  
    bool hasCapitalLetter = false;
    bool hasLowerCaseLetter = false;
    bool hasNumber = false;
    int i;
    for (i = 0; i < size && i < MAX_STR_LENGTH; i++) {
        if (!str[i]) {
            break;
        }
        hasCapitalLetter |= isupper(str[i]) != 0;
        hasLowerCaseLetter |= islower(str[i]) != 0;
        hasNumber |= isdigit(str[i]) != 0;

        if (hasCapitalLetter && hasLowerCaseLetter && hasNumber) {
            return true;
        }
    }
    return false;
}

int main() {
    char str[MAX_STR_LENGTH + 1] = "aB1";
    str[MAX_STR_LENGTH] = '\0';

    int strLength = strnlen(str, sizeof(str));

    if(checkString(str, strLength)) {
        printf("String Passed\n");
    }
    else {
        printf("String Failed\n");
    }

    return 0;
}