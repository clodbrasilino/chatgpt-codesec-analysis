#include <stdbool.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[10] = "aB1";
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);

    if(checkString(str, len)) {
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("String Passed\n");
    }
    else {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("String Failed\n");
    }

    return 0;
}