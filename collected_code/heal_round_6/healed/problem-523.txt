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

    for (int i = 0; i < size && i < MAX_STR_LENGTH; i++) {
        if (str[i] == '\0') {
            break;
        }
        if (isupper(str[i])) {
            hasCapitalLetter = true;
        } else if (islower(str[i])) {
            hasLowerCaseLetter = true;
        } else if (isdigit(str[i])) {
            hasNumber = true;
        }

        if (hasCapitalLetter && hasLowerCaseLetter && hasNumber) {
            return true;
        }
    }
    return false;
}

int main() {
    char str[MAX_STR_LENGTH + 1] = "aB1";
    str[MAX_STR_LENGTH] = '\0';

    int strLength = strnlen(str, MAX_STR_LENGTH + 1);

    if(checkString(str, strLength)) {
        printf("String Passed\n");
    }
    else {
        printf("String Failed\n");
    }

    return 0;
}