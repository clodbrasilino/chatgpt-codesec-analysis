#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool checkString(const char* str, int length) {
    if(str == NULL || length <= 0) {
        return false;
    }

    bool hasCapitalLetter = false;
    bool hasLowerCaseLetter = false;
    bool hasNumber = false;

    for (int i = 0; i < length; i++) {
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
    char str[10] = "aB1";
    int len = strlen(str);

    if(checkString(str, len)) {
        printf("String Passed\n");
    }
    else {
        printf("String Failed\n");
    }

    return 0;
}