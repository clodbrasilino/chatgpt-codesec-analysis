#include <stdbool.h>
#include <string.h>

bool checkString(char* str, int length) {
    bool hasCapitalLetter = false;
    bool hasLowerCaseLetter = false;
    bool hasNumber = false;
    int strLength = strlen(str);

    if (strLength != length) {
        return false;
    }

    for (int i = 0; i < strLength; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            hasCapitalLetter = true;
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            hasLowerCaseLetter = true;
        } else if (str[i] >= '0' && str[i] <= '9') {
            hasNumber = true;
        }

        if (hasCapitalLetter && hasLowerCaseLetter && hasNumber) {
            return true;
        }
    }

    return false;
}