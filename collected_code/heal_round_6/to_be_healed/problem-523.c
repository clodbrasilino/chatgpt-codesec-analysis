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

    for (int i = 0; i < size; i++) {
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_STR_LENGTH + 1] = "aB1";
    str[MAX_STR_LENGTH] = '\0';

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if(checkString(str, strlen(str))) {
        printf("String Passed\n");
    }
    else {
        printf("String Failed\n");
    }

    return 0;
}