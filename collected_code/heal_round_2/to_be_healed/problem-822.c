#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isValidPassword(const char* password) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(password);
    bool hasLowercase = false;
    bool hasUppercase = false;
    bool hasDigit = false;

    if (length < 8) {
        return false;
    }

    for (int i = 0; i < length; i++) {
        if (islower(password[i])) {
            hasLowercase = true;
        } else if (isupper(password[i])) {
            hasUppercase = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
    }

    return (hasLowercase && hasUppercase && hasDigit);
}

int main(){
    const char* password = "password1";
    bool valid = isValidPassword(password);
    return 0;
}