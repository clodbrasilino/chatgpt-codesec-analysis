#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_STR_LENGTH 1024

bool checkString(const char* str) {
    if(str == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(str);

    if(length <= 0 || length > MAX_STR_LENGTH) {
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_STR_LENGTH + 1] = "aB1";
    str[MAX_STR_LENGTH] = '\0';

    if(checkString(str)) {
        printf("String Passed\n");
    }
    else {
        printf("String Failed\n");
    }

    return 0;
}