#include <stdbool.h>
#include <string.h>

bool checkString(char* str, int length) {
    bool hasCapitalLetter = false;
    bool hasLowerCaseLetter = false;
    bool hasNumber = false;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
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