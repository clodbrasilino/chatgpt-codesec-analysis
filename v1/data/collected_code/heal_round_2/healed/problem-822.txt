#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool isValidPassword(const char* password, const size_t size) {
    int length = (int)size;
    bool hasLowercase = false;
    bool hasUppercase = false;
    bool hasDigit = false;

    if (length < 8) {
        return false;
    }

    for (int i = 0; i < length; i++) {
        if (password[i] == '\0') {
            break;
        }
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

int main() {
    const char password[] = "password1";
    bool valid = isValidPassword(password, sizeof(password)-1);
    return 0;
}