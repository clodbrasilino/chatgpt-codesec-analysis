#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_STR_LENGTH 1024

bool checkString(const char* str, int size) {
    if (str == NULL || size < 1 || size > MAX_STR_LENGTH) {
        return false;
    }
  
    bool hasCapitalLetter = false;
    bool hasLowerCaseLetter = false;
    bool hasNumber = false;

    for (int i = 0; i < size && str[i] != '\0'; i++) {
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
    char str[MAX_STR_LENGTH + 1];
    strncpy(str, "aB1", MAX_STR_LENGTH);
    str[MAX_STR_LENGTH] = '\0';

    int strLength = strnlen(str, MAX_STR_LENGTH + 1);
    strLength = strLength > MAX_STR_LENGTH ? MAX_STR_LENGTH : strLength;

    if (checkString(str, strLength)) {
        printf("String Passed\n");
    }
    else {
        printf("String Failed\n");
    }

    return 0;
}